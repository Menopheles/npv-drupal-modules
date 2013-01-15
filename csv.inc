<?php
/**
 * @file 
 * Funktion für den Import von csv-Dateien für die NPV - Module
 * 
 * Die csv-Dateien müssen immer im Format: UTF8 ohne BOM vorliegen.
 * 
 */
define('IMPORT_TYPE_RLEINZEL', 1);
define('IMPORT_TYPE_RLEVENT', 2);
define('IMPORT_TYPE_RLVEREIN', 3);
define('IMPORT_TYPE_LIGA', 4);
define('IMPORT_TYPE_NPVSPIELER', 5);

/**
 * Liest CSV-Datei ein und ersetzt Inhalte in einer Tabelle
 *
 * @param source_file string vollständiger Pfad auf die zu verarbeitende CSV-Datei
 * @param target_table string Tabelle in die der Inhalt der CSV-Datei importiert wird.
 * @param type Importtyp (RLeinzel, event oder verein)
 * @param max_line_length number längste Zeile
 * 
 */
function csv_file_to_mysql_table($source_file, $target_table, $type, $max_line_length=10000) {
  if (($handle = fopen("$source_file", "r")) !== FALSE) {
    $columns = fgetcsv($handle, $max_line_length, ";");
    //drupal_set_message(print_r($columns,TRUE));
    foreach ($columns as &$column) {
      /* eventuell vorhande Dateiformat Kennung für UTF-8 BOM entfernen
       * und Feldnamen in `` setzen.
       */
      $column = '`' . trim(str_replace(".", "", str_replace("\xEF\xBB\xBF", '', $column))) . '`';
    }
    //$insert_query_prefix = "REPLACE INTO `$target_table` (".join(", ",$columns).")\nVALUES";
    $firstrow = TRUE;
    $numrows = 0;
    while (($data = fgetcsv($handle, $max_line_length, ";")) !== FALSE) {
      /* Vor verarbeitung der ersten Datenzeile alle relevanten Daten löschen. */
      if ($firstrow) {
        if ($type == IMPORT_TYPE_RLEINZEL) {
          $num_deleted = db_delete($target_table)
            ->condition('Jahr', $data[43])
            ->execute();
          array_push($columns, 'join_einzel');
        } 
        elseif ($type == IMPORT_TYPE_RLEVENT) {
          $num_deleted = db_delete($target_table)
            ->condition('Jahr', $data[11])
            ->execute();
        } 
        elseif ($type == IMPORT_TYPE_RLVEREIN) { //Hier existieren immer nur die aktuellen Daten.
          $num_deleted = db_delete($target_table)
          ->condition('Jahr', $data[13])
          ->execute();
          array_push($columns, 'join_einzel');
        }
        drupal_set_message(check_plain('Es wurden ' . $num_deleted . ' Datensätze aus Tabelle: ' . $target_table . ' gelöscht.'));
        $firstrow = FALSE;
      }
      /* Bei import event die Spalten 1 = Datum und 2 = letzter Event umwandeln */
      if ($type == IMPORT_TYPE_RLEVENT) {
        if ($data[2] == 'WAHR') {
          $data[2] = '1';//TRUE;
        } 
        else {
          $data[2] = '0';//FALSE;
        }
        /* Datum in UNIX-Time umwandeln.
         * Datum muss das Format "SA 02.07.2011" haben.
         */ 
        $data[1] = mktime(0, 0, 0, substr($data[1], 3, 2), substr($data[1], 0, 2), substr($data[1], 6, 4));
      } 
      elseif ($type == IMPORT_TYPE_RLEINZEL) {
        array_push($data, $data[1] . $data[43]);
      } 
      elseif ($type == IMPORT_TYPE_RLVEREIN) {
        array_push($data, $data[0] . $data[13]);
      }
      /* Falls nicht alle Felder im Datenbereich übergeben wurden, diese mit NULL auffüllen. */
      while (count($data)<count($columns))
        array_push($data, NULL);
      //$query = "$insert_query_prefix (".join(", ",quote_all_array($data)).");";
      //db_query($query);
      $data = quote_all_array($data);
      /* NULL values können nicht über db_insert verarbeitet werden.
       * diese Felder aus dbcolumns- und data-array entfernen.
       */
      $dbcolumns = $columns;
      foreach ($data as $key => $value) {
        if
        ($value == 'NULL') {
          unset($data[$key]);
          unset($dbcolumns[$key]);
        } 
      }
      /* INSERT ausführen */
      db_insert($target_table)
        ->fields($dbcolumns)
        ->values($data)
        ->execute();
      $numrows ++;
    }
    fclose($handle);
    drupal_set_message(check_plain('Es wurden ' . $numrows . ' Datensätze in Tabelle: ' . $target_table . ' hinzugefügt.'));
  } 
  else {
    drupal_set_message(check_plain('Die Datei: ' . $source_file . ' konnte nicht geöffnet werden.</br>Es sind keine Daten verarbeitet worden.'), 'error');
  }
}

function quote_all_array($values) {
  foreach ($values as $key => $value) {
    if (is_array($value)) {
      $values[$key] = quote_all_array($value);
    }
    else {
      $values[$key] = quote_all($value);
    }
  }
  return $values;
}

function quote_all($value) {
  if (is_null($value) || $value == '') {
    return 'NULL';
  }
  if (is_numeric(str_replace(',', '.', $value))) {
    $value = str_replace(',', '.', $value);
  }
  //$value = "'" . mysql_real_escape_string($value) . "'";
  //$value = mysql_real_escape_string($value);
  return $value;
}

/**
 * Liest CSV-Datei ein und ersetzt Inhalte in den Liga Tabellen
 * npv_liga_liga, npv_liga_ligateam, npv_liga_begegnung
 *
 * @param source_file string vollständiger Pfad auf die zu verarbeitende CSV-Datei
 * @param target_table string Tabelle in die der Inhalt der CSV-Datei importiert wird.
 * @param type Importtyp (RLeinzel, event oder verein)
 * @param max_line_length number längste Zeile
 *
 */
function csv_file_to_mysql_table_liga($source_file, $target_table, $type, $max_line_length=10000) {
  if ($target_table !== 'npv_liga' || $type !== IMPORT_TYPE_LIGA) {
    drupal_set_message(t('Die Funktion csv_file_to_mysql_table_liga wurde mit falschen Parametern aufgerufen.'), 'error');
    return;
  } 
  elseif (($handle = fopen("$source_file", "r")) !== FALSE) {
    $data = fgetcsv($handle, $max_line_length, ";");
    //drupal_set_message(print_r($data,TRUE));
    foreach ($data as &$column) {
      /* eventuell vorhande Dateiformat Kennung für UTF-8 BOM entfernen
       * und Feldnamen in `` setzen.
      */
      $column = trim(str_replace(".", "", str_replace("\xEF\xBB\xBF", '', $column)));
    }
    if ($data[0] !== '#liga#') {
      drupal_set_message(t('Fehlerhaftes Dateiformat! keine Liga gefunden.'), 'error');
      return;
    } 
    else {
      $query = db_select('npv_liga_liga', 'a');
      $query  ->fields('a', array('idliga', 'name', 'jahr', 'date_cre'));
      $query  ->condition('a.name', $data[1], '=');
      $query  ->condition('a.jahr', $data[2], '=');
      $result = $query->execute();
      $data1 = $result->fetchAssoc();
      if ($data1 !== FALSE) { // alles für diese ligaid löschen
        $num_deleted = db_delete('npv_liga_begegnung')
        ->condition('idliga', $data1['idliga'])
        ->execute();
        drupal_set_message(check_plain('Es wurden ' . $num_deleted . ' Datensätze aus der Tabelle npv_liga_begegnung gelöscht.'), TRUE);
        $num_deleted = db_delete('npv_liga_ligateam')
        ->condition('idliga', $data1['idliga'])
        ->execute();
        drupal_set_message(check_plain('Es wurden ' . $num_deleted . ' Datensätze aus der Tabelle npv_liga_ligateam gelöscht.'), TRUE);
        $num_deleted = db_delete('npv_liga_liga')
        ->condition('jahr', $data1['jahr'])
        ->condition('name', $data1['name'])
        ->execute();
        drupal_set_message(check_plain('Es wurden ' . $num_deleted . ' Datensätze aus der Tabelle npv_liga_liga gelöscht.'), TRUE);
      }
      // Liga erzeugen
      $idliga = db_insert('npv_liga_liga')
      ->fields(array('name', 'jahr', 'date_cre'))
      ->values(array($data[1], $data[2], REQUEST_TIME))
      ->execute();
      drupal_set_message(check_plain('Liga mit ID: ' . $idliga . ' wurde erstellt.'), TRUE);
    }
    // Teams erzeugen
    $data = fgetcsv($handle, $max_line_length, ";");
    foreach ($data as &$column) {
      $column = trim($column);
    }
    if ($data[0] !== '#verein#') {
      drupal_set_message(t('Fehlerhaftes Dateiformat! kein Vereine gefunden.'), 'error');
      return;
    } 
    else {
      $idteam = db_insert('npv_liga_ligateam')
      ->fields(array('name', 'idliga', 'date_cre'))
      ->values(array($data[1], $idliga, REQUEST_TIME))
      ->execute();
      drupal_set_message(check_plain('Team mit ID: ' . $idteam . ' wurde erstellt.'), TRUE);
      $teams[$data[1]] = $idteam;
    }
    while (($data = fgetcsv($handle, $max_line_length, ";")) !== FALSE && $data[0] == '#verein#') {
      $data = quote_all_array($data);
      $idteam = db_insert('npv_liga_ligateam')
      ->fields(array('name', 'idliga', 'date_cre'))
      ->values(array($data[1], $idliga, REQUEST_TIME))
      ->execute();
      drupal_set_message(check_plain('Team mit ID: ' . $idteam . ' wurde erstellt.'), TRUE);
      $teams[$data[1]] = $idteam;
    }
    //begegnungen erzeugen
    if ($data[0] !== '#spiel#') {
      drupal_set_message(t('Fehlerhaftes Dateiformat! kein Spiele gefunden.'), 'error');
      return;
    } 
    else {
      $numrows = 0;
      $idspiel = db_insert('npv_liga_begegnung')
      ->fields(array('ort', 'date_game', 'uhrzeit', 'bahn', 'idteam1', 'idteam2', 'idliga', 'date_cre'))
      ->values(array($data[1], $data[2], $data[3], $data[4], $teams[$data[5]], $teams[$data[6]], $idliga, REQUEST_TIME))
      ->execute();
      drupal_set_message(check_plain('Spiel mit ID: ' . $idspiel . ' wurde erstellt.'), TRUE);
      $numrows ++;
    }
    while (($data = fgetcsv($handle, $max_line_length, ";")) !== FALSE && $data[0] == '#spiel#') {
      $idspiel = db_insert('npv_liga_begegnung')
      ->fields(array('ort', 'date_game', 'uhrzeit', 'bahn', 'idteam1', 'idteam2', 'idliga', 'date_cre'))
      ->values(array($data[1], $data[2], $data[3], $data[4], $teams[$data[5]], $teams[$data[6]], $idliga, REQUEST_TIME))
      ->execute();
      drupal_set_message(check_plain('Spiel mit ID: ' . $idspiel . ' wurde erstellt.'), TRUE);
      $numrows ++;
    }
    fclose($handle);
    drupal_set_message(check_plain('Es wurden ' . $numrows . ' Datensätze in Tabelle: npv_liga_begegnung hinzugefügt.'));
    //Tabelle erzeugen
    $query = db_select('npv_liga_ligateam', 'a');
    $query -> fields('a');
    $query -> condition('a.idliga', $idliga, '=');
    $result = $query->execute();
    foreach ($result as $team) {
      $query2 = db_select('npv_liga_begegnung', 'a');
      $query2 -> fields('a');
      $query2 -> condition('idliga', $idliga, '=');
      $query2 -> condition('idteam1', $team->idligateam, '=');
      $result2 = $query2->execute();
      $matchpunkte = $siege = $kugeldifferenz = $kugelgewonnen = $siege_selbst = $siege_gegner = $spiele_selbst = $spiele_gegner = $kugeln_selbst = $kugeln_gegner = 0;
      foreach ($result2 as $begegnung) {
        $matchpunkte += $begegnung->matchpunkt_team1;
        $siege += $begegnung->siege_team1;
        $kugeldifferenz += ($begegnung->kugeln_team1 - $begegnung->kugeln_team2);
        $kugelgewonnen += $begegnung->kugeln_team1;
        $siege_selbst += $begegnung->siege_team1;
        $siege_gegner += $begegnung->siege_team2;
        $spiele_selbst += $begegnung->matchpunkt_team1;
        $spiele_gegner += $begegnung->matchpunkt_team2;
        $kugeln_selbst += $begegnung->kugeln_team1;
        $kugeln_gegner += $begegnung->kugeln_team2;
      }
      $query3 = db_select('npv_liga_begegnung', 'a');
      $query3 -> fields('a');
      $query3 -> condition('idliga', $idliga, '=');
      $query3 -> condition('idteam2', $team->idligateam, '=');
      $result3 = $query3->execute();
      foreach ($result3 as $begegnung1) {
        $matchpunkte += $begegnung1->matchpunkt_team2;
        $siege += $begegnung1->siege_team2;
        $kugeldifferenz += ($begegnung1->kugeln_team2 - $begegnung1->kugeln_team1);
        $kugelgewonnen += $begegnung1->kugeln_team2;
        $siege_selbst += $begegnung1->siege_team2;
        $siege_gegner += $begegnung1->siege_team1;
        $spiele_selbst += $begegnung1->matchpunkt_team2;
        $spiele_gegner += $begegnung1->matchpunkt_team1;
        $kugeln_selbst += $begegnung1->kugeln_team2;
        $kugeln_gegner += $begegnung1->kugeln_team1;
      }
      db_merge('npv_liga_ligatabelle')
      ->key(array('idliga' => $idliga, 'idligateam' => $team->idligateam))
      ->fields(array(
          'platz' => 0,
          'matchpunkte' => $matchpunkte,
          'siege' => $siege,
          'kugeldifferenz' => $kugeldifferenz,
          'kugelgewonnen' => $kugelgewonnen,
          'date_cre' => REQUEST_TIME,
          'siege_selbst' => $siege_selbst,
          'siege_gegner' => $siege_gegner,
          'spiele_selbst' => $spiele_selbst,
          'spiele_gegner' => $spiele_gegner,
          'kugeln_selbst' => $kugeln_selbst,
          'kugeln_gegner' => $kugeln_gegner,
      ))
      ->execute();
    }
    drupal_set_message(check_plain('Die Ligatabelle wurde initialisiert.'));
  } 
  else {
    drupal_set_message(check_plain('Die Datei: ' . $source_file . ' konnte nicht geöffnet werden.</br>Es sind keine Daten verarbeitet worden.'), 'error');
  }
}

/**
 * Liest CSV-Datei ein und ersetzt die Informationen der NPV Spieler
 *
 * @param source_file string vollständiger Pfad auf die zu verarbeitende CSV-Datei
 * @param type Importtyp (NPVSpieler)
 * @param max_line_length number längste Zeile
 *
 */
function csv_file_import_spieler($source_file, $type, $max_line_length=10000) {
  if ($type !== IMPORT_TYPE_NPVSPIELER) {
    drupal_set_message(t('Die Funktion csv_file_import_spieler wurde mit falschen Parametern aufgerufen.'), 'error');
    return;
  }
  elseif (($handle = fopen("$source_file", "r")) !== FALSE) {
    if (!csv_checkfilecoding($source_file)) {
      drupal_set_message('Die Zeichensatzkodierung der Datei: '.$source_file.'konnte nicht ermittelt werden.', 'error');
      return;
    }
    $data = fgetcsv($handle, $max_line_length, ";");
    
//    drupal_set_message(print_r($data,TRUE));
//    return;
    foreach ($data as &$column) {
      /* eventuell vorhande Dateiformat Kennung für UTF-8 BOM entfernen
       * und Feldnamen in `` setzen.
      */
      $column = trim(str_replace(".", "", str_replace("\xEF\xBB\xBF", '', $column)));
    }
    if ($data[0] !== '#NPVSpieler#') {
      drupal_set_message(t('Fehlerhaftes Dateiformat! keine NPV Spieler gefunden.'), 'error');
      return;
    }
    else {
      $data = fgetcsv($handle, $max_line_length, ';'); //Zeile mit Spaltenüberschriften
      $data = fgetcsv($handle, $max_line_length, ';'); //Leerzeile
      $numrows = $numrowsverein = $numrowslizenz = $numrowslizenz1 = 0;
      while (($data = fgetcsv($handle, $max_line_length, ";")) !== FALSE && !empty($data[0])) {
        $error = FALSE;
        $vereinsid = _get_vereinsid($data[2]);
        if($vereinsid == -9) {
          drupal_set_message('Der Verein für Spieler '.$data[4].' '.$data[5].' konnte aus der Lizenznr.: '.$data[2].'nicht ermittelt werden.', 'error');
          $numrowsverein ++;
          $error = TRUE;
        }
        elseif($vereinsid == -8) {
          drupal_set_message('Der Lizenznr.: '.$data[2].'existiert schon.', 'error');
          $numrowslizenz ++;
          $error = TRUE;
        }
        $spielerid = _extract_spielerlizenz($data[2]);
        if ($spielerid == -9) {
          drupal_set_message('Die Lizenznr. für Spieler '.$data[4].' '.$data[5].' konnte aus der Lizenznr.: '.$data[2].'nicht ermittelt werden.', 'error');
          $numrowslizenz1 ++;
          $error = TRUE;
        }
        if (!$error) {
          $idspieler = db_insert('npv_spieler')
          ->fields(array('lizenz',
            'idverein',
            'vorname',
            'name',
            'geburts_datum',
            'geschlecht',
            'strasse',
            'plz',
            'ort',
            'telefon',
            'email',
            'date_create',
            'country'))
          ->values(array(_extract_spielerlizenz($data[2]),
            _get_vereinsid($data[2]),
            $data[4],
            $data[5],
            mktime(0, 0, 0, substr($data[6], 3, 2), substr($data[6], 0, 2), substr($data[6], 6, 4)),
            $data[7],
            $data[9],
            $data[10],
            $data[11],
            $data[12],
            $data[13],
            REQUEST_TIME,
            $data[8]))
          ->execute();
          drupal_set_message(check_plain('Spieler '.$data[5].' mit ID: ' . $idspieler . ' wurde erstellt.'), TRUE);
          $numrows ++;
        }
      }
      fclose($handle);
      drupal_set_message(check_plain('Es wurden ' . $numrows . ' Datensätze in Tabelle: npv_spieler hinzugefügt.'));
      if ($numrowsverein > 0) {
        drupal_set_message('Es wurden '.$numrowsverein.' Spieler nicht hinzugefügt, weil der Verein nicht ermittelt werden konnte.');
      }
      if ($numrowslizenz > 0) {
        drupal_set_message('Es wurden '.$numrowslizenz.' Spieler nicht hinzugefügt, weil die Lizenznr. schon existierte.');
      }
      if ($numrowslizenz1 > 0) {
        drupal_set_message('Es wurden '.$numrowslizenz1.' Spieler nicht hinzugefügt, weil die Lizenznr. des Spielers nicht ermittelt werden konnte.');
      }
    }
  }
  else {
    drupal_set_message(check_plain('Die Datei: ' . $source_file . ' konnte nicht geöffnet werden.</br>Es sind keine Daten verarbeitet worden.'), 'error');
  }
}

/**
 * Diese Funktion prüft die Zeichensatzkodierung einer Datei
 * und wandelt sie gegebenenfalls in UTF-8 um.
 *
 * @param string $file Dateiname der zu prüfenden Datei.
 * @return boolean
 */
function csv_checkfilecoding($file) {
  $filedata = file_get_contents($file);
  if ($filedata !== FALSE) {
    /* eigentlich sollte die Kodierung mittels
     * mb_detect_encoding($filedata, 'auto');
     * ermittelt werden, dies ergibt jedoch kein korrektes Ergebnis.
     *
     * Mit folgendem Code kann man die am besten passende Kodierung
     * ermitteln.
     * foreach(mb_list_encodings() as $chr){
     *   echo mb_convert_encoding($text, 'UTF-8', $chr)." : ".$chr."<br>";
     * }
     */
    $kodierung = 'pass';
    if ($kodierung == FALSE) {
      return FALSE;
    } else {
      $filedata_encoded = mb_convert_encoding($filedata, 'UTF-8', $kodierung);
      file_put_contents($file, $filedata_encoded);
      return TRUE;
    }
  } else {
    return FALSE;
  }
}

function _extract_spielerlizenz($npvlizenz) {
  if(strlen($npvlizenz) == 11) {
    return substr($npvlizenz, 8, 3);
  }
  else {
    return -9;
  }
}

function _get_vereinsid($npvlizenz) {
  $query = db_select('npv_vereine', 'a')
    ->fields('a', array('idvereine'))
    ->condition('lizenznr', substr($npvlizenz, 0, 7), '=');
  $result = $query->execute();
  $data = $result ->fetchObject();
  if ($data !== FALSE) {
    $query = db_select('npv_spieler', 'a')
      ->fields('a', array('idverein'))
      ->condition('lizenz', substr($npvlizenz, 8, 3), '=');
    $query ->join('npv_vereine', 'b', 'a.idverein = b.idvereine');
    $query ->condition('b.lizenznr', substr($npvlizenz, 0, 7), '=');
    $result = $query->execute();
    /* @var $data1 mixed Resultset Object */
    $data1 = $result ->fetchObject();
    if ($data1 !== FALSE) {
      return -8;
    }
    else {
      return $data->idvereine;
    }
  }
  else {
    return -9;
  }
}