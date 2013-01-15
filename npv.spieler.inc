<?php
// $Id$
/**
 * @file
 * Alle Funktionen für die Verwaltung von Spielern
 */

/**
 * Erstellt eine Übersichtsseite mit allen Spielern
 *
 * @return string
 */
function npv_spieler_admin() {
  $headers= array(
    array('data' => t('ID'), 'field' => 'idspieler'),
    array('data' => t('Vorname'), 'field' => 'vorname', ),
    array('data' =>  t('Name'), 'field' => 'name', 'sort' => 'asc', ),
    array('data' =>  t('Ort'), 'field' => 'ort', ),
    array('data' =>  t('Verein'), 'field' => 'vname', ),
    array('data' => t('Sperre'), 'field' => 'sperre'),
    array('data' => t('Bearbeiter'), 'field' => 'username', ),
    array('data' => t('letzte Änderung'), 'field' => 'date_last_change', ),
    array('data' => t('Operation'), 'field' => 'operation')
  );

  $rows = array();

  $query = npv_spieler_build_filter_query();
  $query ->orderByHeader($headers);
  $result = $query
    ->limit(20) // Number of records to show per page.
    ->execute();
  foreach ($result as $row) {
    $arow = array();
    $arow['idspieler'] = $row->idspieler;
    $arow['vorname'] = $row->vorname;
    $arow['name'] = $row->name;
    $arow['ort'] = $row->ort;
    $arow['vname'] = $row->vname;
    $arow['sperre'] = $row->sperre;
    $arow['bearbeiter'] = $row->username;
    $arow['date_last_change'] = !empty($row->date_last_change) ? format_date($row->date_last_change, 'short') : 'ohne'; 
    $arow['operation'] = '<ul class="links inline">';
    $arow['operation'] .= '<li class="edit first">'.l(t('Edit'), 'admin/npv/spieler/edit/'.$row->idspieler).'</li>';
    $arow['operation'] .= '<li class="delete">'.l(t('Delete'), 'admin/npv/spieler/edit/' . $row->idspieler).'</li>';
    $arow['operation'] .= '</ul>';
    $rows[] = array('data' => $arow);
  }
  
  // Make the table...
  $build['pager_table'] = array(
      '#theme' => 'table',
      '#header' => $headers,
      '#rows' => $rows,
      '#empty' => 'Keine Daten gefunden.',
  );

  //$build['pager_pager'] = array('#theme' => 'pager');
  return $build;

}

/**
 * Erzeugt eine Ausgabe zur Vereinshistorie eines Spielers.
 * @param $id
 *   Die Id des Spielers
 * @return Inhalt
 */
function npv_get_vhistory($id) {
  $headers= array(
    array('data' => t('von'), 'field' => 'date_from', ),
    array('data' =>  t('bis'), 'field' => 'date_to',  ),
    array('data' =>  t('Verein'), 'field' => 'vname', ),
  );

  $rows = array();

  $query = db_select('npv_shistory', 'a');
  $query ->fields('a');
  $query ->join('npv_vereine', 'b', 'a.idverein = b.idvereine');
  $query ->addField('b', 'name', 'vname');
  $query ->condition('a.idspieler', $id, '=');
  $query ->condition('a.type', 2, '=');

  $result = $query ->execute();

  // Process the query...
  foreach ($result as $row) {
    $rows[] = array(
      'date_from' => date("d.m.Y", $row->date_from),
      'date_to' => date("d.m.Y", $row->date_to),
      'vname' => $row->vname,
    );
  }
 
  // Make the table...
  $output = theme('table', array('header'=>$headers, 'rows'=>$rows, 'empty' => 'Keine Daten gefunden.'));
  
  return $output;
}

/**
 * Erzeugt eine Ausgabe zu den Sperren eines Spielers.
 * @param $id
 *   Die Id des Spielers
 * @return Inhalt
 */
function npv_get_sperrhistory($id) {
  $headers= array(
    array('data' => t('von'), 'field' => 'date_from', ),
    array('data' =>  t('bis'), 'field' => 'date_to', ),
    array('data' =>  t('Bemerkung'), 'field' => 'remark', ),
  );

  $rows = array();

  $query = db_select('npv_shistory', 'a')->extend('PagerDefault');
  $query ->fields('a', array('date_from', 'date_to', 'remark'));
  $query ->condition('idspieler', $id, '=');
  $query ->condition('type', 1, '=');
  $result = $query ->execute();

  // Process the query...
  foreach ($result as $row) {
    $rows[] = array(
      'date_from' => date("d.m.Y", $row->date_from),
      'date_to' => date("d.m.Y", $row->date_to),
      'remark' => $row->remark,
    );
  }
  // Make the table...
  $output = theme('table', array('header'=>$headers, 'rows'=>$rows, 'empty' => 'Keine Daten gefunden.'));

  return $output;
}

/**
 * Erzeugt eine Ausgabe mit Bild und Informationen zu einem Spieler
 * @param $id
 *   Die Id des Spielers
 * @return Inhalt
 */
function npv_get_spieler_info($id) {
  $query = db_select('npv_spieler', 'a');
  $query  ->fields('a');
  $query  ->join('npv_vereine', 'b', 'a.idverein = b.idvereine');
  $query ->addfield('b', 'name', 'vname');
  $query ->addfield('b', 'lizenznr', 'vlic');
  $query ->addfield('b', 'idvereine');
  $query ->condition('a.idspieler', $id, '=');
  $result = $query ->execute();
  $data = $result ->fetchObject();
  $output = '<div class="npv-spieler-info-block">';
  if (!is_null($data->bild)) {
    $output .= '<div class="npv-spieler-info-image"><img src="' . file_create_url($data->bild) . '" width="135" height="175" /></div>';
  }
  $output .= '<div class="npv-spieler-info">';
  $output .= "<p>" . $data->vorname . " " . $data->name . "</p>";
  if ($data->gesperrt == 1) {
    $output .= "<p>Dieser Spieler ist im Zeitraum vom " . date("d.m.Y", $data->gesperrt_von);
    $output .= " bis zum " . date("d.m.Y", $data->gesperrt_bis) . " gesperrt.</p>";
    $output .= "<p>Grund:<br />" . $data->gesperrt_text . "</p>";
  }
  $output .= "<p>Verein: " . $data->vname . ", Lizenz: " . $data->vlic . "-" . $data->lizenz . "</p>";
  $output .= '</div><div class ="npv-clear"></div></div>';
   
  return $output;
}

/**
 * Erstellt eine Seite mit Informationen über alle Spieler
 *
 * @return Seiteninhalt
 */
function npv_spieler_page_long() {
  $sql = "SELECT idspieler FROM {npv_spieler} WHERE del_yn = 0";
  $result = db_query($sql);
  // @todo möglichkeit zum aufteilen in mehrere Seiten mit Seintennavigation
  while ($record = db_fetch_object($result)) {
    $output .= npv_get_spieler_info($record->idspieler);
  }
  return $output;
}

/**
 * Menu callback: Formular zur Bearbeitung von Spielerdaten
 *
 * @param string $op
 *   Der Operationsmodus Standardwert = new für Neulanlage
 *   edit = Editieren eines vorhandenen Spielers
 * @param integer $id 
 *   Die Id des Spielers - nur notwendig beim editieren eines Spielers
 * 
 * @return Formular
 */
function npv_spieler_add_form($form, $form_state, $op = 'new', $id = 0) {
  $form = array();
  if ($op == 'edit') {
    $sql = "SELECT a.*, b.name AS vname, b.lizenznr AS vlic FROM {npv_spieler} AS a, {npv_vereine} AS b";
    $sql .= " WHERE idspieler = %d AND b.idvereine = a.idverein";
    $query = db_select('npv_spieler', 'a');
    $query  ->fields('a');
    $query  ->join('npv_vereine', 'b', 'a.idverein = b.idvereine');
    $query ->addfield('b', 'name', 'vname');
    $query ->addfield('b', 'lizenznr', 'vlic');
    $query ->addfield('b', 'idvereine');
    $query ->condition('a.idspieler', $id, '=');
    $result = $query ->execute();
    $dataspieler = $result ->fetchObject();
    $form['aktion'] = array('#type' => 'hidden', '#value' => 'edit');
    $form['idspieler'] = array('#type' => 'hidden', '#value' => $id);
    $form['altesbild'] = array('#type' => 'hidden', '#value' => $dataspieler->bild);
    $spielertext = npv_get_spieler_info($id); //@todo kann auch den record für die Spielerdaten zurückgeben.
  };
  if (isset($spielertext) && !is_null($spielertext)) {
    $form['spielerbild'] = array(
      '#type' => 'markup',
      '#weight' => '0',
      '#markup' => $spielertext,
    );
  }
  
  $form['bild'] = array(
    '#weight' => '1',
    '#size' => '30',
    '#type' => 'file',
    '#description' => t('Es dürfen nur jpg oder bmp Dateien verwendet werden. Das Bild wird automatisch auf eine Größe von 135 x 175 Pixel skaliert.'),
    '#prefix' => '<table><tr><td>Bild</td><td>',
    '#suffix' => '</td>',
  );
  
  if ($op == 'edit' && !is_null($dataspieler->bild)) {
    $form['bild_delete'] = array(
      '#weight' => '2',
      '#type' => 'checkbox',
      '#title' => 'Bild löschen',
      '#required' => FALSE,
      '#prefix' => '<td colspan="2">',
      '#suffix' => '</td></tr>',
    );
  } else {
    $form['bilddelete'] = array(
      '#weight' => '2',
      '#type' => 'markup',
      '#markup' => '<td colspan="2"></td></tr>',
    );
  }
  
  $form['vorname'] = array(
    '#size' => '60',
    '#weight' => '3',
    '#type' => 'textfield',
    '#maxlength' => 45,
    '#default_value' => isset($dataspieler->vorname) ? $dataspieler->vorname : '',
    '#required' => TRUE,
    '#prefix' => '<tr><td>Vorname</td><td>',
    '#suffix' => '</td>',
  );
  
  $form['name'] = array(
    '#size' => '60',
    '#weight' => '4',
    '#type' => 'textfield',
    '#maxlength' => 45,
    '#default_value' => isset($dataspieler->name) ? $dataspieler->name : '',
    '#required' => TRUE,
    '#prefix' => '<td>Name</td><td>',
    '#suffix' => '</td></tr>',
  );
  $form['country'] = array(
    '#type' => 'select',
    '#weight' => '5',
    '#default_value' => isset($dataspieler->country) ? $dataspieler->country : 'DE',
    '#options' => countries_get_countries('name', array('enabled' => COUNTRIES_ENABLED)),
    '#required' => FALSE,
    '#prefix' => '<tr><td>Nationalität</td><td colspan="3">',
    '#suffix' => '</td></tr>',
  );
  $form['geschlecht'] = array(
    '#weight' => '6',
    '#options' => array( 'm' => 'männlich', 'w' => 'weiblich', ),
    '#type' => 'radios',
    '#default_value' => isset($dataspieler->geschlecht) ? $dataspieler->geschlecht : '',
    '#required' => TRUE,
    '#prefix' => '<tr><td>Geschlecht</td><td>',
    '#suffix' => '</td>',
  );
  $form['geburtsdatum'] = array(
    '#type' => 'date_popup', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
    '#weight' => '7',
    '#default_value' => isset($dataspieler->geburts_datum) ? date("Y-m-d", $dataspieler->geburts_datum) : '',
    '#date_format' => 'd.m.Y',
    '#date_label_position' => 'none', // See other available attributes and what they do in date_api_elements.inc
    '#date_timezone' => '', // Optional, if your date has a timezone other than the site timezone.
    '#date_increment' => 15, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.
    '#date_year_range' => '-100:+0', // Optional, used to set the year range (back 3 years and forward 3 years is the default).
    '#required' => TRUE,
    '#prefix' => '<td>Geburtsdatum</td><td>',
    '#suffix' => '</td></tr>',
  );
  $form['aktiv'] = array(
    '#weight' => '8',
    '#default_value' => 'one',
    '#options' => array( '0' => 'aktiv', '1' => 'inaktiv', '2' => 'gelöscht', ),
    '#type' => 'radios',
    '#default_value' => isset($dataspieler->aktiv) ? $dataspieler->aktiv : '0',
    '#required' => TRUE,
    '#prefix' => '<tr><td>Status</td><td>',
    '#suffix' => '</td><td colspan="2"></td></tr></table>',
  );
  
  if($op == 'new' && !empty($form_state['values']['verein'])) {
    $query = db_select('npv_vereine', 'a')
      ->fields('a', array('idvereine', 'name', 'lizenznr'))
      ->condition('name', $form_state['values']['verein'], '=');
    $result = $query->execute();
    $datav = $result->fetchObject();
    if ($datav !== FALSE) {
      $query = db_select('npv_spieler', 'a')
        ->fields('a', array('lizenz',));
      $query->addExpression('MAX(a.lizenz)', 'lic');
      $query->condition('idverein', $datav->idvereine, '=');
      $result = $query->execute();
      $data1 = $result->fetchObject();
      if($data1 !== FALSE) {
        $licno = sprintf("%03s", $data1->lic+1);
      } else {
        $licno = '000';
      }
    }
  } else {
    $licno = '999';
  }
  $form['verein'] = array(
    '#type' => 'fieldset',
    '#weight' => '9',
    '#title' => t('Vereinszugehörigkeit'),
    '#collapsible' => TRUE,
    '#collapsed' => isset($dataspieler->idvereine) && !($op == 'edit') ? FALSE : TRUE,
    '#prefix' => '<div id="vereinslizenz_div">',
    '#suffix' => '</div>',
  );
  $form['verein']['verein'] = array(
    '#size' => '60',
    '#weight' => '10',
    '#type' => 'textfield',
    '#title' => 'Verein',
    '#autocomplete_path' => 'verein/autocomplete',
    '#default_value' => isset($dataspieler->vname) ? $dataspieler->vname : '',
    '#description' => 'Der Verein des Spielers.',
    '#required' => FALSE,
    '#disabled' => ($op == 'edit') ? TRUE : FALSE,
    '#ajax' => array(
      'callback' => 'ajax_verein_callback',
      'wrapper' => 'vereinslizenz_div',
      'event' => 'blur',
      'method' => 'replaceWith',
     ),
  );
  $form['verein']['vereinslizenz'] = array(
    '#size' => '60',
    '#weight' => '11',
    '#type' => 'textfield',
    '#title' => 'Vereins-Lizenz',
    '#maxlength' => 7,
    '#default_value' => isset($dataspieler->vlic) ? $dataspieler->vlic : '',
    '#description' => 'Die Lizenznummer des Vereins.',
    '#required' => ($op == 'edit') ? FALSE : TRUE,
    '#disabled' => ($op == 'edit') ? TRUE : FALSE,
    '#value' => isset($data1->lizenznr) ? $data1->lizenznr : isset($dataspieler->vlic) ? $dataspieler->vlic : '',
  );
  $form['verein']['vereinsid'] = array(
    '#type' => 'value',
    '#value' => isset($datav->idvereine) ? $datav->idvereine : isset($dataspieler->idvereine) ? $dataspieler->idvereine : '',
  );
  $form['verein']['lizenz'] = array(
    '#size' => '60',
    '#weight' => '12',
    '#type' => 'textfield',
    '#title' => 'Lizenz',
    '#maxlength' => 3,
    '#default_value' => isset($dataspieler->lizenz) ? $dataspieler->lizenz : $licno,
    '#value' => isset($dataspieler->lizenz) ? $dataspieler->lizenz : $licno,
    '#description' => 'Die Lizenznummer des Spielers.',
    '#required' => ($op == 'edit') ? FALSE : TRUE,
    '#disabled' => ($op == 'edit') ? TRUE : FALSE,
  );
  if ($op == 'edit') {
    $form['verein']['vwechsel'] = array(
    '#type' => 'submit',
    '#value' => t('Vereinswechsel'),
    '#weight' => '13',
    '#validate' => array('npv_spieler_vereinswechsel_1'),
  );
  }
  $form['verein']['vhistory'] = array(
    '#type' => 'fieldset',
    '#weight' => '14',
    '#title' => t('Historie'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['verein']['vhistory']['vhistoryinfo'] = array(
    '#type' => 'markup',
    '#weight' => '15',
    '#prefix' => '<div class="npv-spieler-history">',
    '#markup' => isset($dataspieler->idspieler) ? npv_get_vhistory($dataspieler->idspieler) : '',
    '#suffix' => '</div>',
  );
  $form['anschrift'] = array(
    '#type' => 'fieldset',
    '#weight' => '16',
    '#title' => t('Anschrift, Telefon, Email'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['anschrift']['strasse'] = array(
    '#size' => '60',
    '#weight' => '17',
    '#type' => 'textfield',
    '#maxlength' => 45,
    '#default_value' => isset($dataspieler->strasse) ? $dataspieler->strasse : '',
    '#required' => FALSE,
    '#prefix' => '<table><tr><td width="120px">Straße</td><td colspan="2">',
    '#suffix' => '</td></tr>'
  );
  $form['anschrift']['plz'] = array(
    '#size' => '10',
    '#weight' => '18',
    '#type' => 'textfield',
    '#maxlength' => 5,
    '#default_value' => isset($dataspieler->plz) ? $dataspieler->plz : '',
    '#required' => FALSE,
    '#prefix' => '<tr><td>Postleitzahl / Ort</td><td width="50px">',
    '#suffix' => '</td>',
  );

  $form['anschrift']['ort'] = array(
    '#size' => '60',
    '#weight' => '19',
    '#type' => 'textfield',
    '#maxlength' => 45,
    '#default_value' => isset($dataspieler->ort) ? $dataspieler->ort : '',
    '#required' => FALSE,
    '#prefix' => '<td>',
    '#suffix' => '</td></tr>',
  );
  $form['anschrift']['telefon'] = array(
    '#size' => '60',
    '#weight' => '20',
    '#type' => 'textfield',
    '#maxlength' => 45,
    '#default_value' => isset($dataspieler->telefon) ? $dataspieler->telefon : '',
    '#required' => FALSE,
    '#prefix' => '<tr><td>Telefon</td><td colspan="2">',
    '#suffix' => '</td></tr>',
  );
  $form['anschrift']['handy'] = array(
    '#size' => '60',
    '#weight' => '21',
    '#type' => 'textfield',
    '#maxlength' => 45,
    '#default_value' => isset($dataspieler->handy) ? $dataspieler->handy : '',
    '#required' => FALSE,
    '#prefix' => '<tr><td>Handy</td><td colspan="2">',
    '#suffix' => '</td></tr>',
  );
  $form['anschrift']['email'] = array(
    '#size' => '60',
    '#weight' => '22',
    '#type' => 'textfield',
    '#maxlength' => 45,
    '#default_value' => isset($dataspieler->email) ? $dataspieler->email : '',
    '#required' => FALSE,
    '#prefix' => '<tr><td>Email</td><td colspan="2">',
    '#suffix' => '</td></tr></table>',
  );
  $form['sperren'] = array(
    '#type' => 'fieldset',
    '#weight' => '23',
    '#title' => t('Sperren'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['sperren']['gesperrt'] = array(
    '#type' => 'checkbox',
    '#weight' => '24',
    '#default_value' => isset($dataspieler->gesperrt) ? $dataspieler->gesperrt : '0',
    '#required' => FALSE,
    '#prefix' => '<table><tr><td width="120px">Gesperrt</td><td>',
    '#suffix' => '</td></tr>',
  );
  $form['sperren']['sperrevon'] = array(
    '#type' => 'date_popup', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
    '#weight' => '25',
    '#default_value' => isset($dataspieler->gesperrt) && $dataspieler->gesperrt == 1 ? date("Y-m-d", $dataspieler->gesperrt_von) : date("Y-m-d", time()),
    '#date_format' => 'd.m.Y',
    '#date_label_position' => 'none', // See other available attributes and what they do in date_api_elements.inc
    '#date_timezone' => '', // Optional, if your date has a timezone other than the site timezone.
    '#date_increment' => 15, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.
    '#date_year_range' => '-100:+10', // Optional, used to set the year range (back 3 years and forward 3 years is the default).
    '#required' => FALSE,
    '#description' => '',
    '#prefix' => '<tr><td>Von</td><td>',
    '#suffix' => '</td></tr>',
  );
  $form['sperren']['sperrebis'] = array(
    '#type' => 'date_popup', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
    '#weight' => '26',
    '#default_value' => isset($dataspieler->gesperrt) && $dataspieler->gesperrt == 1 ? date("Y-m-d", $dataspieler->gesperrt_bis) : '',
    '#date_format' => 'd.m.Y',
    '#date_label_position' => 'none', // See other available attributes and what they do in date_api_elements.inc
    '#date_timezone' => '', // Optional, if your date has a timezone other than the site timezone.
    '#date_increment' => 15, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.
    '#date_year_range' => '-100:+10', // Optional, used to set the year range (back 3 years and forward 3 years is the default).
    '#required' => FALSE,
    '#prefix' => '<tr><td>Bis</td><td>',
    '#suffix' => '</td></tr>',
  );
  $form['sperren']['bemerkung'] = array(
    '#type' => 'textarea',
    '#weight' => '27',
    '#default_value' => isset($dataspieler->gesperrt) ? $dataspieler->gesperrt_text : '',
    '#size' => '60',
    '#rows' => '3',
    '#wysiwyg' => FALSE,
    '#required' => FALSE,
    '#prefix' => '<tr><td>Bemerkung</td><td>',
    '#suffix' => '</td></tr></table>',
  );
  $form['sperren']['shistory'] = array(
    '#type' => 'fieldset',
    '#weight' => '28',
    '#title' => t('Historie'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['sperren']['shistory']['historyinfo'] = array(
    '#type' => 'markup',
    '#weight' => '29',
    '#prefix' => '<div class="npv-spieler-history">',
    '#value' => isset($dataspieler->idspieler) ? npv_get_sperrhistory($dataspieler->idspieler) : '',
    '#suffix' => '</div>',
  );
  $form['funktion'] = array(
    '#type' => 'fieldset',
    '#weight' => '30',
    '#title' => t('Funktionen'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['funktion']['funktionen'] = array(
    '#type' => 'select',
    '#weight' => '31',
    '#default_value' => 'keine',
    '#options' => array(
      'keine' => t('- keine -'),
      'Präsident' => t('Präsident/In'),
      'Vizepräsident' => t('Vizepräsident/In'),
      'Schatzmeister' => t('Schatzmeister/In'),
      'Sportwart' => t('Sportwart/In'),
      'Ligawart' => t('Ligawart/In'),
      'Jugendwart' => t('Jugendwart/In'),
      'Schiedsrichterwart' => t('Schiedsrichterwart/In'),
      'Ranglistenbeauftragter' => t('Ranglistenbeauftragte/r'),
    ),
    '#required' => FALSE,
    '#prefix' => '<table><tr><td width="120px">Funktion im Verband</td><td>',
    '#suffix' => '</td></tr>',
  );
  $form['funktion']['funkvon'] = array(
    '#type' => 'date_popup', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
    '#weight' => '32',
    '#default_value' => date("Y-m-d", time()),
    '#date_format' => 'd.m.Y',
    '#date_label_position' => 'none', // See other available attributes and what they do in date_api_elements.inc
    '#date_timezone' => '', // Optional, if your date has a timezone other than the site timezone.
    '#date_increment' => 15, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.
    '#date_year_range' => '-100:+10', // Optional, used to set the year range (back 3 years and forward 3 years is the default).
    '#required' => FALSE,
    '#prefix' => '<tr><td>Von</td><td>',
    '#suffix' => '</td></tr>',
  );
  $form['funktion']['funkbis'] = array(
    '#type' => 'date_popup', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
    '#weight' => '33',
    '#default_value' => '',
    '#date_format' => 'd.m.Y',
    '#date_label_position' => 'none', // See other available attributes and what they do in date_api_elements.inc
    '#date_timezone' => '', // Optional, if your date has a timezone other than the site timezone.
    '#date_increment' => 15, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.
    '#date_year_range' => '-100:+10', // Optional, used to set the year range (back 3 years and forward 3 years is the default).
    '#required' => FALSE,
    '#prefix' => '<tr><td>Bis</td><td>',
    '#suffix' => '</td></tr></table>',
  );
  $form['funktion']['fhistory'] = array(
    '#type' => 'fieldset',
    '#weight' => '34',
    '#title' => t('Historie'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['funktion']['fhistory']['fhistoryinfo'] = array(
    '#type' => 'markup',
    '#weight' => '35',
    '#prefix' => '<div class="npv-sperren">',
    '#value' => 'Ausgabe einer Tabelle mit allen Funktionen.',
    '#suffix' => '</div>',
  );

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
  $form['#attributes'] = array('class' => 'npv', 'enctype' => "multipart/form-data");
   
  return $form;
}

/**
 * Menu Callback Anlage eines Spielers
 *
 * @return
 *   Formular
 */
function npv_spieler_add() {
  //drupal_add_js(drupal_get_path('module', 'npv') . '/npv.js', 'modul');
  return drupal_get_form('npv_spieler_add_form');
}

//@TODO:  Validierung der Eingaben
function npv_spieler_add_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Cancel')) {
    drupal_get_messages('error');
    drupal_goto('admin/npv/spieler');
  }
  /*$sql = "SELECT idvereine FROM {npv_vereine} where lizenznr = '%s'";
  $result = db_query($sql, $form_state['values']['vereinslizenz']);
  if ($record = db_fetch_object($result)) {
    form_set_value($form['verein']['vereinsid'], $record->idvereine, $form_state);
  }
  else {
    form_set_error('vereinslizenz', 'Es existiert kein Verein zur angegebenen Vereinslizenz-Nummer.');
  }*/
  
}

/**
 * Submit handler für das Spieler Formular
 *
 * Verarbeitung der Formulareingaben
 *
 * @param $form
 *     Das Formular
 * @param $form_state
 *     Die Werte des Formulars
 */
function npv_spieler_add_form_submit($form, &$form_state) {
  global $user;
  if ($form_state['values']['bilddelete'] == '1') {
    if (isset($form_state['values']['idspieler'])) {
      $sql = "SELECT bild FROM {npv_spieler} WHERE idspieler = %d";
      $result = db_query($sql, $form_state['values']['idspieler']);
      $record = db_fetch_object($result);
      if (!is_null($record->bild)) {
        file_delete($record->bild);
        $value = array(
          'idspieler' => $form_state['values']['idspieler'],
          'bild' => '',
        );
        drupal_write_record('npv_spieler', $value, 'idspieler');
      }
    }
  }
  else {
    $validators = array( 'file_validate_extensions' => array('jpg bmp')); //Erlaubte Datei-Endungen
    //Pfad des Ordners, wo die Uploads gespeichert werden
    $upload_path = 'public://'.variable_get('npv_path1', '');
    if ($file = file_save_upload('bild', $validators, 'temporary://', $replace = FILE_EXISTS_REPLACE)) {
      if (isset($form_state['values']['idspieler'])) {
        $sql = "SELECT bild FROM {npv_spieler} WHERE idspieler = :d";
        $query = db_select('npv_spieler', 'a')
          ->fields('a', array('bild',))
          ->condition('idspieler', $form_state['values']['idspieler'], '=');
        $result = $query->execute();
        $data = $result ->fetchObject();
        if (!is_null($data->bild)) {
          drupal_unlink($data->bild);
        }
      }
      
      $file->status |= FILE_STATUS_PERMANENT;
      $file = file_save($file);
      file_move($file, $upload_path, $replace = FILE_EXISTS_REPLACE);
      $imgSmall = image_load($upload_path.'/'.$file->filename);
      image_resize($imgSmall, 135, 175);
      image_save($imgSmall,$upload_path.'/'.$file->filename);
      $bild = $upload_path.'/'.$file->filename;
      drupal_set_message(check_plain("Upload erfolgreich<br />" . $bild));
    }
    else {
      drupal_set_message(t('Fehler beim Upload des Bildes oder kein Bild angegeben.'), 'warning');
    }
  }
  $values = array('idspieler' => isset($form_state['values']['idspieler']) ? $form_state['values']['idspieler'] : 0,
      'vorname' => $form_state['values']['vorname'],
      'name' => $form_state['values']['name'],
      'geschlecht' => $form_state['values']['geschlecht'],
      'aktiv' => $form_state['values']['aktiv'],
      'idverein' => $form_state['values']['vereinsid'],
      'geburts_datum' => mktime(0, 0, 0, substr($form_state['values']['geburtsdatum'], 5, 2), substr($form_state['values']['geburtsdatum'], 8, 2), substr($form_state['values']['geburtsdatum'], 0, 4)),
      'strasse' => $form_state['values']['strasse'],
      'plz' => $form_state['values']['plz'],
      'ort' => $form_state['values']['ort'],
      'telefon' => $form_state['values']['telefon'],
      'handy' => $form_state['values']['handy'],
      'email' => $form_state['values']['email'],
      'country' => $form_state['values']['country'],
      'bild' => isset($bild) && !empty($bild) ? $bild : $form_state['values']['altesbild'],
      'uid' => $user->uid,
  );
  drupal_set_message('uid:'.$user->uid);
  if (!isset($form_state['values']['idspieler'])) {
    $values['lizenz'] = $form_state['values']['lizenz'];
  }
  if ($form_state['values']['gesperrt'] == '1') {
    $values['gesperrt'] = '1';
    $values['gesperrt_von'] = mktime(0, 0, 0, substr($form_state['values']['sperrevon'], 5, 2), substr($form_state['values']['sperrevon'], 8, 2), substr($form_state['values']['sperrevon'], 0, 4));
    $values['gesperrt_bis'] = mktime(0, 0, 0, substr($form_state['values']['sperrebis'], 5, 2), substr($form_state['values']['sperrebis'], 8, 2), substr($form_state['values']['sperrebis'], 0, 4));
    $values['gesperrt_text'] = $form_state['values']['bemerkung'];
  }
  if (isset($form_state['values']['aktion'])) {
    $values['date_last_change'] = time();
    if (drupal_write_record('npv_spieler', $values, 'idspieler')) {
      drupal_set_message(check_plain('Die Daten des Spielers ' . $values['vorname'] . ' ' . $values['name'] . ' wurden erfolgreich aktualisiert!'));
    }
    else {
      drupal_set_message(check_plain('Die Daten des Spielers ' . $values['vorname'] . ' ' . $values['name'] . ' konnten aufgrund eines Datenbankproblems nicht aktualisiert werden!'), 'error');
    }
  }
  else {
    $values['date_last_change'] = time();
    $values['date_create'] = time();
    if (drupal_write_record('npv_spieler', $values)) {
      drupal_set_message(check_plain('Der Spieler ' . $values['vorname'] . ' ' . $values['name'] . ' wurde erfolgreich angelegt!'));
    }
    else {
      drupal_set_message(check_plain('Der Spieler ' . $values['vorname'] . ' ' . $values['name'] . ' konnte aufgrund eines Datenbankproblems nicht angelegt werden!'), 'error');
    }
  }
  drupal_goto('admin/npv/spieler');
}

/**
 * Menüaufruf zum editieren eines Spielers
 *
 * @param $id
 *  Die Id des Spielers
 * @return
 *   Formular
 */
function npv_spieler_edit($id) {
  return drupal_get_form('npv_spieler_add_form', 'edit', $id);
}

/**
 * Menüaufruf für den Vereinswechsel eines Spieler
 * @param $id
 *   Die Id des Spielers
 * @return Formular
 */
function npv_spieler_vereinswechsel($id) {
  //drupal_add_js(drupal_get_path('module', 'npv') . '/npv.js');
  return drupal_get_form('npv_spieler_vereinswechsel_form', 'change', $id);
}

/**
 * Hilfsfunktion zum Aufruf des Formulars zum Vereinswechsel eines Spielers
 * aus dem Formular zum Editieren eines Spielers
 *
 * @param $form
 *   Das Formular
 * @param $form_state
 *   Die Formularwerte
 */
function npv_spieler_vereinswechsel_1($form, &$form_state) {
  drupal_goto('admin/npv/spieler/vereinswechsel/' . $form_state['values']['idspieler']);
}

/**
 * Erzeugt das Formular für einen Vereinswechsel
 * @param $form_state
 *   Die Formularwerte
 * @param $op
 *   Der Operationsmodus: change
 * @param $id
 *   Die Id des Spielers
 * @return Formular
 */
function npv_spieler_vereinswechsel_form($form, $form_state, $op = 'change', $id) {
  $form = array();

  $query = db_select('npv_spieler', 'a');
  $query ->fields('a', array('vorname', 'name', 'lizenz', 'eintritt'));
  $query ->join('npv_vereine', 'b', 'a.idverein = b.idvereine');
  $query ->condition('a.idspieler', $id, '=');
  $query ->addfield('b', 'name', 'vname');
  $query ->addfield('b',  'lizenznr', 'vlic');
  $query ->addfield('b', 'idvereine');
  $result = $query->execute();
  $data = $result->fetchObject();
  
  $form['aktion'] = array('#type' => 'hidden', '#value' => 'edit');
  $form['idspieler'] = array('#type' => 'hidden', '#value' => $id);
  $form['idvereinold'] = array('#type' => 'hidden', '#value' => $data->idvereine);
  $form['eintrittold'] = array('#type' => 'hidden', '#value' => $data->eintritt);
  $txt = "<p>Der Spieler <b>" . $data->vorname . " " . $data->name . "</b> wechselt von <b>";
  $txt .= $data->vname . "</b> mit der Lizenz-Nr.: <b>" . $data->vlic . "-" . $data->lizenz . "</b> zu:</p>";
  $form['info'] = array(
    '#type' => 'markup',
    '#weight' => '0',
    '#prefix' => '<div class="npv-vereinswechsel">',
    '#markup' => $txt,
    '#suffix' => '</div>',
  );
  if($op == 'change' && !empty($form_state['values']['verein'])) {
    $query = db_select('npv_vereine', 'a')
      ->fields('a', array('idvereine', 'name', 'lizenznr'))
      ->condition('name', $form_state['values']['verein'], '=');
    $result = $query->execute();
    $datav = $result->fetchObject();
    if ($datav !== FALSE) {
      $query = db_select('npv_spieler', 'a')
        ->fields('a', array('lizenz',));
      $query->addExpression('MAX(a.lizenz)', 'lic');
      $query->condition('idverein', $datav->idvereine, '=');
      $result = $query->execute();
      $data1 = $result->fetchObject();
      if($data1 !== FALSE) {
        $licno = sprintf("%03s", $data1->lic+1);
      } else {
        $licno = '000';
      }
    }
  } else {
    $licno = '999';
  }
  $form['verein'] = array(
    '#type' => 'fieldset',
    '#weight' => '1',
    '#title' => t('Vereinszugehörigkeit'),
    '#collapsible' => FALSE,
    '#prefix' => '<div id="vereinslizenz_div">',
    '#suffix' => '</div>',
  );
  $form['verein']['verein'] = array(
    '#size' => '60',
    '#weight' => '2',
    '#type' => 'textfield',
    '#title' => 'Verein',
    '#autocomplete_path' => 'verein/autocomplete',
    '#default_value' => '',
    '#description' => 'Der neue Verein des Spielers.',
    '#required' => FALSE,
    '#ajax' => array(
      'callback' => 'ajax_verein_callback',
      'wrapper' => 'vereinslizenz_div',
      'event' => 'blur',
      'method' => 'replaceWith',
     ),
  );
  $form['verein']['vereinslizenz'] = array(
    '#size' => '60',
    '#weight' => '3',
    '#type' => 'textfield',
    '#title' => 'Vereins-Lizenz',
    '#maxlength' => 7,
    '#default_value' => isset($datav->lizenznr) ? $datav->lizenznr : '',
    '#description' => 'Die Lizenznummer des neuen Vereins.',
    '#required' => TRUE,
    '#value' => isset($datav->lizenznr) ? $datav->lizenznr : '',
  );
  $form['verein']['lizenz'] = array(
    '#size' => '60',
    '#weight' => '4',
    '#type' => 'textfield',
    '#title' => 'Lizenz',
    '#maxlength' => 3,
    '#default_value' => isset($licno) && !empty($licno) ? $licno : '',
    '#description' => 'Die Lizenznummer des Spielers.',
    '#required' => TRUE,
    '#value' => isset($licno) && !empty($licno) ? $licno : '',
  );
  $form['verein']['austritt'] = array(
    '#type' => 'date_popup', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
    '#title' => 'Austritt am',
    '#weight' => '5',
    '#default_value' => date("Y-m-d", time()),
    '#date_format' => 'd.m.Y',
    '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
    '#date_timezone' => '', // Optional, if your date has a timezone other than the site timezone.
    '#date_increment' => 15, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.
    '#date_year_range' => '-10:+10', // Optional, used to set the year range (back 3 years and forward 3 years is the default).
    '#required' => TRUE,
  );
  $form['eintritt'] = array(
    '#type' => 'date_popup', // types 'date_text' and 'date_timezone' are also supported. See .inc file.
    '#title' => 'Eintritt am',
    '#weight' => '6',
    '#default_value' => date("Y-m-d", time()),
    '#date_format' => 'd.m.Y',
    '#date_label_position' => 'within', // See other available attributes and what they do in date_api_elements.inc
    '#date_timezone' => '', // Optional, if your date has a timezone other than the site timezone.
    '#date_increment' => 15, // Optional, used by the date_select and date_popup elements to increment minutes and seconds.
    '#date_year_range' => '-10:+10', // Optional, used to set the year range (back 3 years and forward 3 years is the default).
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#weight' => '99',
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form['#attributes'] = array('class' => 'npv');
  return $form;
}

/**
 * Submit Handler für das Vereinswechsel Formular
 * @param $form
 *   Das Formular
 * @param $form_state
 *   Die Formularwerte
 */
function npv_spieler_vereinswechsel_form_submit($form, &$form_state) {
  $sql = "SELECT idvereine FROM {npv_vereine} where lizenznr = '%s'";
  $query = db_select('npv_vereine', 'a')
    ->fields('a', array('idvereine'))
    ->condition('lizenznr', $form_state['values']['vereinslizenz'], '=');
  $result = $query ->execute();
  $record = $result ->fetchObject();
  if ($record !== FALSE) {
    $vlic = $record->idvereine;
  }
  else {
    // irgendwas ist faul.
  }

  $values = array('idspieler' => $form_state['values']['idspieler'],
    'hid' => '0',
    'type' => '2',
    'date_from' => $form_state['values']['eintrittold'],
    'date_to' => mktime(0, 0, 0, substr($form_state['values']['austritt'], 5, 2), substr($form_state['values']['austritt'], 8, 2), substr($form_state['values']['austritt'], 0, 4)),
    'idverein' => $form_state['values']['idvereinold'],
  );
  // schreibe history daten
  if (drupal_write_record('npv_shistory', $values)) {
      drupal_set_message(check_plain('Der Vereinswechsel des Spielers ' . $values['vorname'] . ' ' . $values['name'] . ' wurde erfolgreich in die Historien-Tabelle geschrieben!'));
  }
  else {
    drupal_set_message(check_plain('Der Vereinswechsel des Spielers ' . $values['vorname'] . ' ' . $values['name'] . ' konnte aufgrund eines Datenbankproblems nicht in der Historien-Tabelle protokolliert werden!'), 'error');
  }
  $values1 = array(
    'idspieler' => $form_state['values']['idspieler'],
    'lizenz' => $form_state['values']['lizenz'],
    'idverein' => $vlic,
    'eintritt' => mktime(0, 0, 0, substr($form_state['values']['eintritt'], 5, 2), substr($form_state['values']['eintritt'], 8, 2), substr($form_state['values']['eintritt'], 0, 4)),
  );
  if (drupal_write_record('npv_spieler', $values1, 'idspieler')) {
      drupal_set_message(check_plain('Der Vereinswechsel des Spielers ' . $values['vorname'] . ' ' . $values['name'] . ' wurde erfolgreich durchgeführt!'));
      drupal_goto('admin/npv/spieler');
  }
  else {
    drupal_set_message(check_plain('Der Vereinswechsel des Spielers ' . $values['vorname'] . ' ' . $values['name'] . ' konnte aufgrund eines Datenbankproblems nicht durchgeführt werden!'), 'error');
  }
}

function ajax_verein_callback($form, $form_state) {
  return $form['verein'];
}

/**
 * Erzeugt die Formulardefinition zum Importieren von Spielern aus einer
 * CSV-Datei
 *
 * @param array $form_state
 *
 * @return array Formulardefinition
 */
function npv_spieler_import_form($form, &$form_state) {

  $form['file_spieler'] = array(
      '#type' => 'file',
      '#title' => t('Spieler Datei'),
      '#description' => t('Import-Datei für NPV-Spieler.'),
  );
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Validierung der Formulareingaben für den Spieler Import
 *
 * @param array $form
 *     		Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 */
function npv_spieler_import_form_validate($form, &$form_state) {
  $file = file_save_upload('file_spieler', array(
      'file_validate_extensions' => array('csv'), // Validate extensions.
  ));
  // If the file passed validation:
  if ($file) {
    // Move the file, into the Drupal file system
    if ($file = file_move($file, 'public://import', FILE_EXISTS_REPLACE)) {
      // Save the file for use in the submit handler.
      $form_state['storage']['file_spieler'] = $file;
    }
    else {
      form_set_error('file_spieler', t('Failed to write the uploaded file the site\'s file folder.'));
    }
  }
  else {
    $form_state['storage']['file_spieler'] = FALSE;
  }
}

/**
 * Submit handler für das Spieler Formular
 *
 * Verarbeitung der Formulareingaben
 *
 * @param array $form
 *     		Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 */
function npv_spieler_import_form_submit($form, &$form_state) {
  $fileeinzel = $form_state['storage']['file_spieler'];
  // We are done with the file, remove it from storage.
  unset($form_state['storage']['file_spieler']);
  if ($fileeinzel) {
    // Make the storage of the file permanent
    $fileeinzel->status = FILE_STATUS_PERMANENT;
    // Save file status.
    file_save($fileeinzel);
    // Set a response to the user.
    $fileeinzel->destination = drupal_realpath('public://import/' . $fileeinzel->filename);
    drupal_set_message(t('Die Datei wurde hochgeladen und gespeichert, Dateiname: @filename.', array('@filename' => $fileeinzel->destination)));
  }
  else {
    drupal_set_message(t('Es wurde keine Datei für die Einzelübersicht hochgeladen.'));
  }
  /* Verarbeitung der Daten
   */
  if ($fileeinzel) {
    include_once '' . drupal_get_path('module', 'npv') . '/csv.inc';
    csv_file_import_spieler(drupal_realpath('public://import/' . $fileeinzel->filename), IMPORT_TYPE_NPVSPIELER);
  }
}

function npv_spieler_export(){
  module_load_include('inc', 'phpexcel', 'phpexcel');

  $data = array();
  $headers = array();

  // First worksheet

  // Get the nodes
  $query = db_select('npv_spieler', 'a');
  $query  ->fields('a');
  //$query  ->orderBy('lizenz');
  $query  ->join('npv_vereine', 'b', 'a.idverein = b.idvereine');
  $query ->addfield('b', 'name', 'vname');
  $query ->addfield('b', 'lizenznr', 'vlic');
  $query  ->orderBy('vlic');
  $query  ->orderBy('lizenz');
  // gesetzte Filter berücksichtigen
  $filter_data = isset($_SESSION['npv_spieler_filter']) ? $_SESSION['npv_spieler_filter'] : array();
  
  foreach ($filter_data as $filter) {
    switch ($filter['0']) {
      case 'verein':
        $query->condition('b.name', _npv_get_spielerfilter($filter['2'], $filter['1']), _npv_get_spielerfilteroperator($filter['1']));
        break;
      case 'name':
        $query->condition('a.name', _npv_get_spielerfilter($filter['2'], $filter['1']), _npv_get_spielerfilteroperator($filter['1']));
        break;
      case 'ort':
        $query->condition('a.ort', _npv_get_spielerfilter($filter['2'], $filter['1']), _npv_get_spielerfilteroperator($filter['1']));
        break;
    }
  }
  
  $result = $query ->execute();

  $prev_verein = '';
  
  while($row = $result ->fetchObject()) {
    if (!count($headers)) {
      // Add the headers for the first worksheet
      $headers['Nodes'] = array(
        'Nr.', ' ', 'Lizenz', 'Verein', 'Vorname', 'Name', 'Geb.Dat.',
        'Geschl.', 'Nationalität', 'Straße', 'PLZ', 'Ort', 'Tel.', 'Handy', 'email',
      );
    }

    // Add the data
    //$data['Nodes'][] = array_values($row);
    if ($prev_verein != $row->vlic) {
      $data['Nodes'][] = array('','','','','','','','','','','','','','','',);
    }
    $data['Nodes'][] = array(
      $row->idspieler, ' ', $row->vlic.'-'.$row->lizenz, $row->vname,
      $row->vorname, $row->name, date("d.m.Y", $row->geburts_datum), $row->geschlecht,
      $row->country, $row->strasse, $row->plz, $row->ort, $row->telefon, $row->handy, $row->email,
    );
    $prev_verein = $row->vlic;
  }
/*
  // Second worksheet

  // Get the latest revisions
  $result = db_query("SELECT {node_revisions}.nid, {node_revisions}.vid, {node_revisions}.title, {node_revisions}.body FROM {node_revisions}
                        LEFT JOIN {node} ON {node}.nid = {node_revisions}.nid AND {node}.vid = {node_revisions}.vid");

  while($row = db_fetch_array($result)) {
    if (count($headers) == 1) {
      // Add the headers for the second worksheet
      $headers['Revisions'] = array_keys($row);
    }

    // Add the data
    $data['Revisions'][] = array_values($row);
  }
*/
  
  // Store the file in sites/default/files
  //$path = file_directory_path() . '/exportspieler.xls';
  $path = drupal_realpath('public://exportspieler.xls');
  // Use the .xls format
  $options = array('format' => 'xls');

  if (phpexcel_export($headers, $data, $path, $options)) {
    drupal_set_message(t("We did it !"));
  }
  else {
    drupal_set_message(t("Oops ! An error occured !"), 'error');
  }

  return 'Die Datei '.l('Spielerexport', file_create_url('public://exportspieler.xls')).' kann jetzt heruntergeladen werden.';
}

function npv_spieler_import_xls() {
  module_load_include('inc', 'phpexcel', 'phpexcel.api');

  // The path to the excel file
  $path = 'sites/default/files/export.xls';
  $path = drupal_realpath('public://import/HH JPC Lizenzen 2012.xlsx');
  $data = phpexcel_import($path);

  if ($data) {
    drupal_set_message(t("We did it !"));
    return '<pre>'.print_r($data, true).'</pre>';
  }
  else {
    drupal_set_message(t("Oops ! An error occured !"), 'error');
  }
}

/**
 * Menu callback: Spieler Verwaltung.
 */
function npv_spieler_admin_form($form, $form_state) {
  
  $form['filter'] = npv_spieler_filter_form();
  $form['#submit'][] = 'npv_spieler_filter_form_submit';
  $form['admin'] = npv_spieler_admin();

  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

function npv_spieler_filter_form_submit($form, $form_state) {
  switch ($form_state['values']['op']) {
    case t('Filter'):
    case t('Refine'):
      unset($_SESSION['npv_spieler_filter']);
      if (isset($form_state['values']['vereinsfilter']) && !empty($form_state['values']['vereinsfilter'])) {
        $_SESSION['npv_spieler_filter'][] = array('verein', $form_state['values']['verein'], $form_state['values']['vereinsfilter']);
      }
      if (isset($form_state['values']['namefilter']) && !empty($form_state['values']['namefilter'])) {
        $_SESSION['npv_spieler_filter'][] = array('name', $form_state['values']['name'], $form_state['values']['namefilter']);
      }
      if (isset($form_state['values']['ortfilter']) && !empty($form_state['values']['ortfilter'])) {
        $_SESSION['npv_spieler_filter'][] = array('ort', $form_state['values']['ort'], $form_state['values']['ortfilter']);
      }
      break;
  }
}

function npv_spieler_filter_form() {
  $filteroptions = array('Ist gleich' => 'Ist gleich',
    'Ist nicht gleich' => 'Ist nicht gleich',
    'Beginnt mit' => 'Beginnt mit',
    'Beginnt nicht mit' => 'Beginnt nicht mit',
    'Enthält' => 'Enthält',
    'Enthält nicht' => 'Enthält nicht',
    'Endet mit' => 'Endet mit',
    'Endet nicht mit' => 'Endet nicht mit',
  );

  $filters = isset($_SESSION['npv_spieler_filter']) ? $_SESSION['npv_spieler_filter'] : array();
  
  foreach ($filters as $filt) {
    switch ($filt['0']) {
      case 'verein':
        $filter['verein']['op'] = $filt['1'];
        $filter['verein']['value'] = $filt['2'];
        break;
      case 'name':
        $filter['name']['op'] = $filt['1'];
        $filter['name']['value'] = $filt['2'];
        break;
      case 'ort':
        $filter['ort']['op'] = $filt['1'];
        $filter['ort']['value'] = $filt['2'];
        break;
    }
  }
  $form['filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Show only items where'),
    '#theme' => 'exposed_filters__node',
    '#attributes' => array('id' => 'npv_filter'),
  );
  
  $form['filters']['status'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('clearfix')),
    //'#prefix' => ($i ? '<div class="additional-filters">' . t('and where') . '</div>' : ''),
  );
  $form['filters']['status']['filters'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filters')),
  );

  // Verein
  $form['filters']['status']['filters']['verein'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filterfilters')),
  );
  $form['filters']['status']['filters']['verein']['verein'] = array(
    '#type' => 'select',
    '#options' => $filteroptions,
    '#title' => 'Verein',
    '#default_value' => isset($filter['verein']['op']) ? $filter['verein']['op'] : 'Enthält',
  );
  $form['filters']['status']['filters']['verein']['vereinsfilter'] = array(
    '#type' => 'textfield',
    '#size' => '60',
    '#maxlength' => 45,
    '#default_value' => isset($filter['verein']['value']) ? $filter['verein']['value'] : '',
    '#required' => FALSE,
  );

  // Name
  $form['filters']['status']['filters']['name'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filterfilters')),
  );
  $form['filters']['status']['filters']['name']['name'] = array(
    '#type' => 'select',
    '#options' => $filteroptions,
    '#title' => 'Name',
    '#default_value' => isset($filter['name']['op']) ? $filter['name']['op'] : 'Enthält',
  );
  $form['filters']['status']['filters']['name']['namefilter'] = array(
    '#type' => 'textfield',
    '#size' => '60',
    '#maxlength' => 45,
    '#default_value' => isset($filter['name']['value']) ? $filter['name']['value'] : '',
    '#required' => FALSE,
  );

  // Ort
  $form['filters']['status']['filters']['ort'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filterfilters')),
  );
  $form['filters']['status']['filters']['ort']['ort'] = array(
    '#type' => 'select',
    '#options' => $filteroptions,
    '#title' => 'Ort',
    '#default_value' => isset($filter['ort']['op']) ? $filter['ort']['op'] : 'Enthält',
  );
  $form['filters']['status']['filters']['ort']['ortfilter'] = array(
    '#type' => 'textfield',
    '#size' => '60',
    '#maxlength' => 45,
    '#default_value' => isset($filter['ort']['value']) ? $filter['ort']['value'] : '',
    '#required' => FALSE,
  );

  $form['filters']['status']['actions'] = array(
    '#type' => 'actions',
    '#attributes' => array('class' => array('container-inline')),
  );
  $form['filters']['status']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Filter') //count($session) ? t('Refine') : t('Filter'),
  );
  return $form;
}

/**
 * Apply filters for node administration filters based on session.
 *
 * @param $query
 *   A SelectQuery to which the filters should be applied.
 */
function npv_spieler_build_filter_query() {
  // Build query
  $query = db_select('npv_spieler', 'a')->extend('PagerDefault')->extend('TableSort');
  $query  ->fields('a', array('idspieler', 'vorname', 'name', 'ort', 'date_last_change'));
  $query  ->join('npv_vereine', 'b', 'a.idverein = b.idvereine');
  $query  ->addfield('b', 'name', 'vname');
  $query  ->join('users', 'c', 'a.uid = c.uid');
  $query  ->addfield('c', 'name', 'username');
  $query  ->addExpression("CASE WHEN a.gesperrt = 1 THEN 'gesperrt' ELSE '' END", 'sperre');

  $filter_data = isset($_SESSION['npv_spieler_filter']) ? $_SESSION['npv_spieler_filter'] : array();
  
  foreach ($filter_data as $filter) {
    switch ($filter['0']) {
      case 'verein':
        $query->condition('b.name', _npv_get_spielerfilter($filter['2'], $filter['1']), _npv_get_spielerfilteroperator($filter['1']));
        break;
      case 'name':
        $query->condition('a.name', _npv_get_spielerfilter($filter['2'], $filter['1']), _npv_get_spielerfilteroperator($filter['1']));
        break;
      case 'ort':
        $query->condition('a.ort', _npv_get_spielerfilter($filter['2'], $filter['1']), _npv_get_spielerfilteroperator($filter['1']));
        break;
    }
  }
  return $query;
}

function _npv_get_spielerfilteroperator($filter) {
  $filteroperator = '=';
  switch ($filter) {
    case 'Ist gleich':
      $filteroperator = '=';
      break;
    case 'Ist nicht gleich':
      $filteroperator = '!=';
      break;
    case 'Beginnt mit':
    case 'Enthält':
    case 'Endet mit':
      $filteroperator = 'like';
      break;
    case 'Beginnt nicht mit':
    case 'Enthält nicht':
    case 'Endet nicht mit':
      $filteroperator = 'not like';
  }
  return $filteroperator;
}

function _npv_get_spielerfilter($filter, $filteroperator) {
  $filtertext = $filter;
  switch ($filteroperator) {
    case 'Ist gleich':
    case 'Ist nicht gleich':
      $filtertext = $filter;
      break;
    case 'Beginnt mit':
    case 'Beginnt nicht mit':
      $filtertext = $filter.'%';
      break;
    case 'Enthält':
    case 'Enthält nicht':
      $filtertext = '%'.$filter.'%';
      break;
    case 'Endet mit':
    case 'Endet nicht mit':
      $filtertext = '%'.$filter;
      break;
  }
  return $filtertext;
}