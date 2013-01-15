<?php
/**
 * @file 
 * Funktionen für das Bearbeiten der Ligaergebnisse für das Modul NPG-Liga
 */

/**
 * Menüaufruf zur Anzeige des Formulars Ligaergebnisse
 * 
 * @param integer $idliga
 * 
 * @return array Eingabeformular
 */
function npv_liga_result_edit($idliga) {
  /* prüfen ob liga existiert */
  $query = db_select('npv_liga_liga', 'a');
  $query  ->addExpression('MAX(jahr)', 'jahraktuell');
  $result = $query->execute();
  $data = $result->fetchAssoc();
  if ($data !== FALSE) {
    $query = db_select('npv_liga_liga', 'a');
    $query ->condition('jahr', $data['jahraktuell'], '=');
    $query ->condition('idliga', $idliga, '=');
    $query ->fields('a', array('idliga', 'name'));
    $result = $query ->execute();
    $data1 = $result->fetchObject();
    if ($data1 === FALSE) {
      return 'Die angeforderte Liga mit ID: ' . $idliga . ' existiert nicht oder gehört nicht zum aktuellen Ligajahr.';
    } 
    else {
      return drupal_get_form('npv_liga_result_edit_form', $idliga);
    }
  } 
  else {
    return 'Die angeforderte Liga mit ID: ' . $idliga . ' existiert nicht.';
  }
}

/**
 * Erzeugt die Formulardefinition zum Erfassen der Ligaergebnisse
 * 
 * @param array $form
 *        Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 * @param Integer $idliga
 *        ID der Liga für die die Ergebnisse bearbeitet werden sollen.
 * 
 * @return array Formulardefinition
 */
function npv_liga_result_edit_form($form, $form_state, $idliga) {
  $query = db_select('npv_liga_liga', 'a');
  $query ->condition('idliga', $idliga, '=');
  $query ->fields('a', array('idliga', 'name'));
  $result = $query ->execute();
  $liga = $result->fetchObject();
  $form = array();
  $form['info'] = array(
      '#markup' => 'Ergebnisse für die Liga ' . $liga->name . ' bearbeiten.',
      '#weight' => '0',
  );
  $form['idliga'] = array(
      '#type' => 'hidden',
      '#default_value' => $idliga,  
  );
  $query = db_select('npv_liga_begegnung', 'a');
  $query -> fields('a');
  $query -> join('npv_liga_ligateam', 'b', 'b.idligateam = a.idteam1');
  $query -> addField('b', 'name', 'nameteam1');
  $query -> join('npv_liga_ligateam', 'c', 'c.idligateam = a.idteam2');
  $query -> addField('c', 'name', 'nameteam2');
  $query -> condition('a.idliga', $idliga, '=');
  $query -> condition('b.name', 'spielfrei', '!=');
  $query -> condition('c.name', 'spielfrei', '!=');
  $query -> orderBy('idbegegnung', 'ASC');
  $result = $query->execute();
  $spieldatum = 0;
  foreach ($result as $begegnung) {
    if ($spieldatum !== $begegnung->date_game) {
      $spieldatum = $begegnung->date_game;
      $spieltag = date("d.m.Y", $begegnung->date_game);
      $form[$begegnung->date_game] = array(
        '#type' => 'fieldset',
        '#title' => check_plain(t('Spieltag: ' . $spieltag)),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
    }
    $form[$begegnung->date_game][$begegnung->idbegegnung] = array(
        '#type' => 'fieldset',
        '#title' => check_plain(t('Begegnung: ' . $begegnung->idbegegnung)),
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
    );
    $form[$begegnung->date_game][$begegnung->idbegegnung][$begegnung->idbegegnung . '/team1'] = array(
        '#size' => '30',
        '#type' => 'textfield',
        '#maxlength' => 100,
        '#default_value' => $begegnung->nameteam1,
        '#description' => 'Heim.',
        '#disabled' => TRUE,        
    );
    $form[$begegnung->date_game][$begegnung->idbegegnung][$begegnung->idbegegnung . '/team2'] = array(
        '#size' => '30',
        '#type' => 'textfield',
        '#maxlength' => 45,
        '#default_value' => $begegnung->nameteam2,
        '#description' => 'Gast.',
        '#disabled' => TRUE,
    );
    $form[$begegnung->date_game][$begegnung->idbegegnung][$begegnung->idbegegnung . '/siege_team1'] = array(
        '#size' => '3',
        '#type' => 'textfield',
        '#maxlength' => 1,
        '#default_value' => $begegnung->siege_team1,
        '#description' => 'Siege Heim.',
        '#disabled' => FALSE,
        '#rules' => array(array('rule' => 'digit', 'error' => $begegnung->idbegegnung . ' : Es sind nur numerische Werte erlaubt.'), ),
    );
    $form[$begegnung->date_game][$begegnung->idbegegnung][$begegnung->idbegegnung . '/siege_team2'] = array(
        '#size' => '3',
        '#type' => 'textfield',
        '#maxlength' => 1,
        '#default_value' => $begegnung->siege_team2,
        '#description' => 'Siege Gast.',
        '#disabled' => FALSE,
        '#rules' => array(array('rule' => 'digit', 'error' => $begegnung->idbegegnung . ' : Es sind nur numerische Werte erlaubt.'), ),
    );
    $form[$begegnung->date_game][$begegnung->idbegegnung][$begegnung->idbegegnung . '/kugeln_team1'] = array(
        '#size' => '3',
        '#type' => 'textfield',
        '#maxlength' => 2,
        '#default_value' => $begegnung->kugeln_team1,
        '#description' => 'Kugeln Heim.',
        '#disabled' => FALSE,
        '#rules' => array(array('rule' => 'digit', 'error' => $begegnung->idbegegnung . ' : Es sind nur numerische Werte erlaubt.'), ),
    );
    $form[$begegnung->date_game][$begegnung->idbegegnung][$begegnung->idbegegnung . '/kugeln_team2'] = array(
        '#size' => '3',
        '#type' => 'textfield',
        '#maxlength' => 2,
        '#default_value' => $begegnung->kugeln_team2,
        '#description' => 'Kugeln Gast.',
        '#disabled' => FALSE,
        '#rules' => array(array('rule' => 'digit', 'error' => $begegnung->idbegegnung . ' : Es sind nur numerische Werte erlaubt.'), ),
    );
  }
  /*$form['bemerkung'] = array(
      '#size' => '50',
      '#type' => 'text_format',
      //'#title' => 'Kugeln Gast',
      '#maxlength' => 255,
      '#default_value' => '',
      '#description' => 'Bemerkung.',
      '#format' => 'Filtered HTML',
      '#disabled' => FALSE,
  );*/
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
  );
  /*$form['actions']['delete'] = array(
   '#type' => 'button',
      '#value' => t('Delete'),
  );*/
  $form['actions']['cancel'] = array(
      '#type' => 'button',
      '#value' => t('Cancel'),
  );
  return $form;
}

/**
 * Validierung für das Ergebnismeldeformular
 * 
 * @param array $form
 *        Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 */
function npv_liga_result_edit_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Cancel')) {
    drupal_get_messages('error');
    $query = db_select('npv_liga_liga', 'a');
    $query -> fields('a');
    $query -> condition('a.idliga', $form_state['values']['idliga'], '=');
    $result = $query->execute();
    $data = $result->fetchObject();
    if ($data !== FALSE) {
      drupal_goto('npv-ligaergebnisse/' . $data->name);
    }
    form_set_error('info', 'Abbrechen ist nicht möglich.');
  }
  $query = db_select('npv_liga_begegnung', 'a');
  $query -> fields('a');
  $query -> join('npv_liga_ligateam', 'b', 'b.idligateam = a.idteam1');
  $query -> addField('b', 'name', 'nameteam1');
  $query -> join('npv_liga_ligateam', 'c', 'c.idligateam = a.idteam2');
  $query -> addField('c', 'name', 'nameteam2');
  $query -> condition('a.idliga', $form_state['values']['idliga'], '=');
  $query -> condition('b.name', 'spielfrei', '!=');
  $query -> condition('c.name', 'spielfrei', '!=');
  $query -> orderBy('idbegegnung', 'ASC');
  $result = $query->execute();
  if ($result === FALSE) {
    form_set_error('info', 'Die Liga mit der ID: ' . $form_state['values']['idliga'] . ' existiert nicht.');
  } 
  else {
    foreach ($result as $begegnung) {
      $kugeln1 = $form_state['values'][$begegnung->idbegegnung . '/kugeln_team1'];
      $kugeln2 = $form_state['values'][$begegnung->idbegegnung . '/kugeln_team2'];
      $siege1 = $form_state['values'][$begegnung->idbegegnung . '/siege_team1'];
      $siege2 = $form_state['values'][$begegnung->idbegegnung . '/siege_team2'];
      if ($siege1 !== '' && $siege2 !== '' && $kugeln1 !== '' && $kugeln2 !== '') {
        if (($siege1 + $siege2) !== 5) {
          form_set_error($begegnung->idbegegnung . '/siege_team1', $begegnung->idbegegnung . ': Die Summe der Felder "Siege Heim" und "Siege Gast" muss 5 betragen.');
        }
        if ($kugeln1 < ($siege1 * 13)) {
          form_set_error($begegnung->idbegegnung . '/kugeln_team1', $begegnung->idbegegnung . ': Die Anzahl der Kugeln im Feld "Kugeln Heim" muss mindestens ' . ($siege1 * 13) . ' betragen.');
        }
        if ($kugeln2 < ($siege2 * 13)) {
          form_set_error($begegnung->idbegegnung . '/kugeln_team2', $begegnung->idbegegnung . ': Die Anzahl der Kugeln im Feld "Kugeln Gast" muss mindestens ' . ($siege2 * 13) . ' betragen.');
        }
        if ($kugeln1 > (($siege1 * 13) + ($siege2 * 12))) {
          form_set_error($begegnung->idbegegnung . '/kugeln_team1', $begegnung->idbegegnung . ': Die Anzahl der Kugeln im Feld "Kugeln Heim" kann nicht größer als ' . (($siege1 * 13) + ($siege2 * 12)) . ' sein.');
        }
        if ($kugeln2 > (($siege2 * 13) + ($siege1 * 12))) {
          form_set_error($begegnung->idbegegnung . '/kugeln_team2', $begegnung->idbegegnung . ': Die Anzahl der Kugeln im Feld "Kugeln Gast" kann nicht größer als ' . (($siege2 * 13) + ($siege1 * 12)) . ' sein.');
        }
      }
    }
  }
}

/**
 * Submit handler für das Ergebnismeldeformular
 *
 * Verarbeitung der Formulareingaben
 * 
 * @param array $form
 *        Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 */
function npv_liga_result_edit_form_submit($form, $form_state) {
  $query = db_select('npv_liga_begegnung', 'a');
  $query -> fields('a');
  $query -> join('npv_liga_ligateam', 'b', 'b.idligateam = a.idteam1');
  $query -> addField('b', 'name', 'nameteam1');
  $query -> join('npv_liga_ligateam', 'c', 'c.idligateam = a.idteam2');
  $query -> addField('c', 'name', 'nameteam2');
  $query -> condition('a.idliga', $form_state['values']['idliga'], '=');
  $query -> condition('b.name', 'spielfrei', '!=');
  $query -> condition('c.name', 'spielfrei', '!=');
  $query -> orderBy('idbegegnung', 'ASC');
  $result = $query->execute();
  if ($result === FALSE) {
    form_set_error('info', 'Die Liga mit der ID: ' . $form_state['values']['idliga'] . ' existiert nicht.');
  } 
  else {
    foreach ($result as $begegnung) {
      $kugeln1 = $form_state['values'][$begegnung->idbegegnung . '/kugeln_team1'];
      $kugeln2 = $form_state['values'][$begegnung->idbegegnung . '/kugeln_team2'];
      $siege1 = $form_state['values'][$begegnung->idbegegnung . '/siege_team1'];
      $siege2 = $form_state['values'][$begegnung->idbegegnung . '/siege_team2'];
      if ($siege1 !== '' && $siege2 !== '' && $kugeln1 !== '' && $kugeln2 !== '') {
        if ($siege1 > $siege2) {
          $matchpunkt1 = 1;
          $matchpunkt2 = 0;
        } 
        else {
          $matchpunkt1 = 0;
          $matchpunkt2 = 1;
        }
        $num_updated = db_update('npv_liga_begegnung')
          ->fields(array(
              'siege_team1' => $siege1,
              'siege_team2' => $siege2,
              'kugeln_team1' => $kugeln1,
              'kugeln_team2' => $kugeln2,
              'matchpunkt_team1' => $matchpunkt1,
              'matchpunkt_team2' => $matchpunkt2,
              'date_ame' => REQUEST_TIME,
          ))
          ->condition('idbegegnung', $begegnung->idbegegnung, '=')
          ->execute();
        if ($num_updated === 0) {
          drupal_set_message(check_plain(t('Für Begegnung ID: ' . $begegnung->idbegegnung . ' wurden keine Daten aktualisiert.')), 'error', TRUE);
        } 
        else {
          $query = db_update('npv_liga_liga')
            ->fields(array(
                'freigabe' => 0,
            ))
            -> condition('idliga', $form_state['values']['idliga'], '=')
            -> execute();
        }
      }
      else {
        // ergebnis zurücksetzen.
        $num_updated = db_update('npv_liga_begegnung')
          ->fields(array(
              'siege_team1' => NULL,
              'siege_team2' => NULL,
              'kugeln_team1' => NULL,
              'kugeln_team2' => NULL,
              'matchpunkt_team1' => NULL,
              'matchpunkt_team2' => NULL,
              'date_ame' => REQUEST_TIME,
          ))
          ->condition('idbegegnung', $begegnung->idbegegnung, '=')
          ->execute();
        if ($num_updated === 0) {
          drupal_set_message(check_plain(t('Für Begegnung ID: ' . $begegnung->idbegegnung . ' wurden keine Daten aktualisiert.')), 'error', TRUE);
        }
        else {
          $query = db_update('npv_liga_liga')
            ->fields(array(
                'freigabe' => 0,
            ))
            -> condition('idliga', $form_state['values']['idliga'], '=')
            -> execute();
        }
      }
    }
  }
  // Ligatabelle aktualisieren (neu erstellen)
  $query = db_select('npv_liga_ligateam', 'a');
  $query -> fields('a');
  $query -> condition('a.idliga', $form_state['values']['idliga'], '=');
  $result = $query->execute();
  foreach ($result as $team) {
    $query2 = db_select('npv_liga_begegnung', 'a');
    $query2 -> fields('a');
    $query2 -> condition('idliga', $form_state['values']['idliga'], '=');
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
    $query3 -> condition('idliga', $form_state['values']['idliga'], '=');
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
    ->key(array('idliga' => $form_state['values']['idliga'], 'idligateam' => $team->idligateam))
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
  //ligatabelle sortieren und platz aktualisieren.
  $query = db_select('npv_liga_ligatabelle', 'a');
  $query -> fields('a');
  $query -> condition('idliga', $form_state['values']['idliga'], '=');
  $query -> orderBy('matchpunkte', 'DESC');
  $query -> orderBy('siege', 'DESC');
  $query -> orderBy('kugeldifferenz', 'DESC');
  $query -> orderBy('kugelgewonnen', 'DESC');
  $result = $query->execute();
  $platz = 1;
  $matchpunkte = $siege = $kugeldifferenz = $kugelgewonnen = -1;
  foreach ($result as $tabelle) {
    db_merge('npv_liga_ligatabelle')
    ->key(array('idliga' => $tabelle->idliga, 'idligateam' => $tabelle->idligateam))
    ->fields(array('platz' => $platz, ))
    ->execute();
    if ($matchpunkte !== $tabelle->matchpunkte && $siege !== $tabelle->siege && $kugeldifferenz !== $tabelle->kugeldifferenz && $kugelgewonnen !== $tabelle->kugelgewonnen) {
      $platz++;
    }
  }
  // Ergebnisseite anzeigen
  $query = db_select('npv_liga_liga', 'a');
  $query -> fields('a');
  $query -> condition('a.idliga', $form_state['values']['idliga'], '=');
  $result = $query->execute();
  $data = $result->fetchObject();
  if ($data !== FALSE) {
    drupal_goto('npv-ligaergebnisse/' . $data->name);
  }
}
/* Hilfsfunktionen */
