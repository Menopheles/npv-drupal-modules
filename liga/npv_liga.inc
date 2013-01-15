<?php
/**
 * @file 
 * Funktionen für die Ligaverwaltung 
 * Modul: NPV-Liga
 */

/**
 * Übersichtsseite für die Ligaverwaltung
 * 
 *  @return string Seiteninhalt
 */
function npv_liga_page() {
  $query = db_select('npv_liga_liga', 'a');
  $query  ->addExpression('MAX(jahr)', 'jahraktuell');
  $result = $query->execute();
  $data = $result->fetchAssoc();
  if ($data !== FALSE) {
    $text = 'Das aktuelle Ligajahr ist ' . $data['jahraktuell'] . '</br>';
    $text .= 'Folgende Ligen sind angelegt:</br>';
    foreach (_npv_liga_get_liga_array() as $liga) {
      $text .= $liga['idliga'] . ' = ' . $liga['name'] . '</br>';
    }
  } 
  else {
    $text = 'Es sind keine Ligen definiert.';
  }
  return $text;
}

/**
 * Menüaufruf zur Anzeige des Upload-Formulars zum Importieren einer Liga
 * 
 * @return array Eingabeformular
 */
function npv_liga_import() {
  return drupal_get_form('npv_liga_import_form');
}

/**
 * Erzeugt die Formulardefinition zum Importieren einer Liga
 * 
 * @param array $form_state
 * 
 * @return array Formulardefinition
 */
function npv_liga_import_form($form_state) {
  // If you are familiar with how browsers handle files, you know that
  // enctype="multipart/form-data" is required. Drupal takes care of that, so
  // you don't need to include it yourself.

  $form['file_liga'] = array(
      '#type' => 'file',
      '#title' => t('Liga Datei'),
      '#description' => t('Import-Datei für eine Liga.'),
  );
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
  );
  
  return $form;
}

/**
 * Validierung der Formulareingaben für den Liga Import
 * 
 * @param array $form
 *     		Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 */
function npv_liga_import_form_validate($form, &$form_state) {
  $file = file_save_upload('file_liga', array(
      'file_validate_extensions' => array('csv'), // Validate extensions.
  ));
  // If the file passed validation:
  if ($file) {
    // Move the file, into the Drupal file system
    if ($file = file_move($file, 'public://import', FILE_EXISTS_REPLACE)) {
      // Save the file for use in the submit handler.
      $form_state['storage']['file_liga'] = $file;
    }
    else {
      form_set_error('file_liga', t('Failed to write the uploaded file the site\'s file folder.'));
    }
  } 
  else {
    $form_state['storage']['file_liga'] = FALSE;
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
function npv_liga_import_form_submit($form, &$form_state) {
  $fileeinzel = $form_state['storage']['file_liga'];
  // We are done with the file, remove it from storage.
  unset($form_state['storage']['file_liga']);
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
    csv_file_to_mysql_table_liga(drupal_realpath('public://import/' . $fileeinzel->filename), 'npv_liga', IMPORT_TYPE_LIGA);
  }
}

/**
 * Generierung der Übersichtsseite für Rechteverwaltung.
 * 
 * @return array Seiteninhalt
 */
function npv_liga_rechte() {
  $text = "Hier werden die Rechte der Benutzer verwaltet, die Ergebnisse einzelner Ligen online melden.</br>";
  $text .= "Für jeden Benutzer ist die Liga-ID bzw. wenn mehr wie eine Liga von dem Benutzer bearbeitet wird,";
  $text .= " die Liga-ID's getrennt durch Semikolon anzugeben.</br>";
  
  $headers= array(
      array('data' =>  t('Name'), 'field' => 'name', 'sort' => 'asc', ),
      array('data' =>  t('Rechte'), ), // 'field' => 'melderechte', ),
      array('data' =>  t('Delete'), ),
  );
  
  // Create a place to store the rows when we process the query in a few moments.
  // This is just like making a table in Drupal.
  $rows = array();
  
  $query = db_select('npv_liga_rechte', 'a')->extend('PagerDefault');
  $query  ->join('users', 'b', 'a.uid = b.uid');
  $query ->addfield('b', 'name', 'name');
  $query  ->fields('a', array('melderechte'));
  $result = $query
  ->limit(20) // Number of records (or nodes, in our case) to show per page.
  ->execute();
  foreach ($result as $row) {
    $row->del = l(t('Delete'), 'liga/ligarights/delete/' . $row->name);
    $row->name = l($row->name, 'liga/ligarights/edit/' . $row->name);
    $rows[] = array('data' => (array) $row);
  }
  
  // Make the table...
  $build['pager_table'] = array(
      '#theme' => 'table',
      '#header' => $headers,
      '#rows' => $rows,
      '#empty' => 'Keine Daten gefunden.',
  );
  // Return the output with the pager attached to it.  The pager
  // is the box underneath the table that allows people to jump
  // to the next page.
  $build['pager_pager'] = array('#theme' => 'pager');
  $build['#prefix'] = $text;
  $text = l(t('Neuer Benutzer'), 'liga/ligarights/add', array('attributes' => array('class' => array('button'))));
  $text .= '</br>Ligen:</br>';
  foreach (_npv_liga_get_liga_array() as $liga) {
    $text .= $liga['idliga'] . ' = ' . $liga['name'] . '</br>';
  }
  $build['#suffix'] = $text;
  return $build;
}

/**
 * Menüaufruf zur Anzeige des Formulars zum Bearbeiten der Rechte eines Users.
 *
 * @return array Eingabeformular
 */
function npv_liga_rechte_edit($uname) {
  return drupal_get_form('npv_liga_rechte_add_form', 'edit', $uname);
}

/**
 * Menüaufruf zur Anzeige des Formulars zur Neuanlage der Rechte eines Users.
 *
 * @return array Eingabeformular
 */
function npv_liga_rechte_add() {
  return drupal_get_form('npv_liga_rechte_add_form');
}

/**
 * Erzeugt die Formulardefinition zum Anlegen/Editieren der Rechte eines Users
 * 
 * @param array $form_state
 *        Die Werte des Formulars
 * @param string $op
 *        Der Operationsmodus Standardwert = new für Neulanlage
 * 	      edit = Editieren eines vorhandenen Spielers
 * @param string $uname
 *        Im edit-modus der Name des Users, sonst leer
 * 
 * @return array Formulardefinition
 */
function npv_liga_rechte_add_form($form, $form_state, $op = 'new', $uname = '') {
  if ($op == 'edit' && $uname !== '') {
    $query = db_select('npv_liga_rechte', 'a');
    $query  ->fields('a');
    $query  ->join('users', 'u', 'a.uid = u.uid');
    $query  ->addField('u', 'name');
    $query  ->condition('u.name', $uname, '=');
    $result = $query->execute();
    $data = $result->fetchObject();
    if ($data !== FALSE) {
      $form['aktion'] = array('#type' => 'hidden', '#value' => 'edit');
    }
  }
  $form['name'] = array(
      '#size' => '90',
      '#weight' => '0',
      '#type' => 'textfield',
      '#autocomplete_path' => 'liga/ligarights/name/autocomplete',
      '#title' => 'Name',
      '#default_value' => isset($data->name) ? $data->name : '',
      '#maxlength' => 60,
      '#description' => 'Der Name des Users. Der User muss der Rolle "Ligamelder" angehören.',
      '#required' => TRUE,
  );
  foreach (_npv_liga_get_liga_array() as $liga) {
    $ligen[$liga['idliga']] = $liga['name'];
  }
  $form['melderechte'] = array(
      '#type' => 'checkboxes',
      '#default_value' => isset($data->melderechte) ? explode(';', $data->melderechte) : array(),
      '#options' => $ligen,
      '#title' => t('Welche Ligen soll dieser User bearbeiten?'),
      '#weight' => '1',
  );
  $form['uid'] = array(
      '#type' => 'hidden',
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
 * Validierung der Formulareingaben für das Rechteformular
 * 
 * @param array $form
 *        Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 */
function npv_liga_rechte_add_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Cancel')) {
    drupal_get_messages('error');
    drupal_goto('liga/ligarights');
  }
  $account = user_load_by_name($form_state['values']['name']);
  if ($account !== FALSE) {
    if (array_search('Ligamelder', $account->roles) === FALSE) {
      form_set_error('name', 'Der user muss der Rolle "Ligamelder" angehören.');
    } 
    else {
      form_set_value($form['uid'], $account->uid, $form_state);
      $query = db_select('npv_liga_rechte', 'a');
      $query  ->fields('a', array('uid', 'melderechte'));
      $query  ->condition('uid', $account->uid, '=');
      $result = $query->execute();
      $data = $result->fetchAssoc();
      if ($data !== FALSE && !isset($form_state['values']['aktion'])) {
        form_set_error('name', 'Es sind für den User: ' . $form_state['values']['name'] . 'bereits Rechte für die Ligen: ' . $data['melderechte'] . ' vergeben');
      }
    }
  } 
  else {
    form_set_error('name', 'Es muss ein angelegter User verwendet werden.');
  }
  $melderechte = _npv_liga_get_melderechte_string_from_form($form_state);
  if (strlen($melderechte) == 0) {
    form_set_error('melderechte', 'Es wurde für keine Liga ein Recht vergeben! Zum löschen der Rechte eines Users bitte das Löschformular verwenden.');
  }
}

/**
 * Submit handler für das Rechte Formular
 *
 * Verarbeitung der Formulareingaben
 * 
 * @param array $form
 *        Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 */
function npv_liga_rechte_add_form_submit($form, &$form_state) {
  $melderechte = '';
  $melderechte = _npv_liga_get_melderechte_string_from_form($form_state);
  db_merge('npv_liga_rechte')
  ->key(array('uid' => $form_state['values']['uid']))
  ->fields(array(
      'melderechte' => $melderechte,
  ))
  ->execute();
  drupal_set_message(check_plain('Rechte für User: ' . $form_state['values']['name'] . ' wurden gespeichert.'), 'status', TRUE);
  drupal_goto('liga/ligarights');
}

/**
 * Menüaufruf zur Anzeige des Formulars zum Löschen der Rechte eines Users.
 *
 * @param string Name des Users
 * @return array Eingabeformular
 */
function npv_liga_rechte_del($uname) {
  return drupal_get_form('npv_liga_rechte_del_form', $uname);
}

/**
 * Erzeugt die Formulardefinition zum Löschen der Rechte eines Users
 * 
 * @param array $form
 *        Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 * @param  string $uname
 *         Name des Users
 * @return array Formulardefinition
 */
function npv_liga_rechte_del_form($form, $form_state, $uname) {
  $form = array();
  if ($uname !== '') {
    $query = db_select('npv_liga_rechte', 'a');
    $query  ->fields('a');
    $query  ->join('users', 'u', 'a.uid = u.uid');
    $query  ->addField('u', 'name');
    $query  ->condition('u.name', $uname, '=');
    $result = $query->execute();
    $data = $result->fetchObject();
    if ($data !== FALSE) {
      $form['uid'] = array(
          '#type' => 'hidden',
          '#default_value' => $data->uid,
      );
      $form['name'] = array(
          '#type' => 'hidden',
          '#default_value' => $data->name,
      );
      $form['aktion'] = array('#type' => 'hidden', '#value' => 'edit');
      $form['info'] = array(
          '#markup' => 'Sollen alle Rechte für den User: ' . $data->name . ' gelöscht werden?',
      );
      $form['actions'] = array('#type' => 'actions');
      $form['actions']['delete'] = array(
          '#type' => 'button',
          '#value' => t('Delete'),
      );
      $form['actions']['cancel'] = array(
          '#type' => 'button',
          '#value' => t('Cancel'),
      );
      $form['#attributes'] = array('class' => 'npv', 'enctype' => "multipart/form-data");
      return $form;
    } 
    else {
      drupal_set_message(check_plain('Es existieren keine Ligarechte für den User: ' . $uname), 'error', TRUE);
      drupal_goto('liga/ligarights');
    }
  } 
  else {
    drupal_set_message(t('Kein User angegeben.'), 'warning', TRUE);
    drupal_goto('liga/ligarights');
  }
}

/**
 * Validierung für das Löschformular der Ligarechte
 * 
 * @param array $form
 *        Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 */
function npv_liga_rechte_del_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Cancel')) {
    drupal_get_messages('error');
    drupal_goto('liga/ligarights');
  } 
  elseif ($form_state['values']['op'] == t('Delete')) {
    form_execute_handlers('submit', $form, $form_state);
  }
}

/**
 * Submit handler für das Löschen der Ligarechte
 *
 * Verarbeitung der Formulareingaben
 * 
 * @param array $form
 *        Das Formular
 * @param unknown_type $form_state
 *        Die Werte des Formulars
 */
function npv_liga_rechte_del_form_submit($form, &$form_state) {
  if ($form_state['values']['op'] == t('Delete')) {
    $num_deleted = db_delete('npv_liga_rechte')
        ->condition('uid', $form_state['values']['uid'])
        ->execute();
    if ($num_deleted > 0) {
      drupal_set_message(check_plain('Die Ligarechte für den User: ' . $form_state['values']['name'] . ' wurden gelöscht.'), 'status', TRUE);
    } 
    else {
      drupal_set_message(check_plain('Die Ligarechte für den User: ' . $form_state['values']['name'] . ' konnten nicht gelöscht werden.'), 'error', TRUE);
    }
    drupal_goto('liga/ligarights');
  }
}

/**
 * Menüaufruf zur Anzeige des Formulars zum Löschen der Rechte eines Users.
 *
 * @return array Eingabeformular
 */
function npv_liga_admin() {
  return drupal_get_form('npv_liga_admin_form');
}


function npv_liga_admin_form($form, &$form_state) {
  $query = db_select('npv_liga_liga', 'a');
  $query  ->addExpression('MAX(jahr)', 'jahraktuell');
  $query ->fields('a');
  $result = $query->execute();
  $data = $result->fetchObject();
  if ($data !== FALSE) {
    $ligajahr = $data->jahraktuell;
  } 
  else {
    return 'Keine Daten vorhanden.';
  }
  $query = db_select('npv_liga_liga', 'a');
  $query ->fields('a');
  $query ->condition('jahr', $ligajahr, '=');
  $query ->orderBy('idliga');
  $result = $query->execute();
  if ($result !== FALSE) {
    $form['firstrow'] = array(
        '#markup' => '<table><tr><th colspan="4"></th><th colspan="4">Begegnungen / nicht gemeldet</th><th></th></tr><tr><th>Liga</th><th>Teams</th><th>Aufsteiger</th><th>1. Abstiegsplatz</th><th>Tag 1</th><th>Tag 2</th><th>Tag 3</th><th>Tag 4</th><th>Freigabe</th></tr>',
    );
    foreach ($result as $liga) {
      $query = db_select('npv_liga_begegnung', 'a');
      $query ->addExpression('count(idbegegnung)', 'anzahl');
      $query ->condition('idliga', $liga->idliga, '=');
      $query ->groupBy('date_game');
      $result1 = $query->execute();
      $i = 1;
      unset($beganz);
      foreach ($result1 as $beg) {
        $beganz[$i] = $beg->anzahl;
        $i++;
      }
      $query = db_select('npv_liga_begegnung', 'a');
      $query ->addExpression('count(idbegegnung)', 'anzahl');
      $query ->condition('idliga', $liga->idliga, '=');
      $query ->isNotNull('siege_team1');
      $query ->groupBy('date_game');
      $result1 = $query->execute();
      $i = 1;
      foreach ($result1 as $beg) {
        $anzgemeldet[$i] = $beganz[$i] - $beg->anzahl;
        $i++;
      }
      $query = db_select('npv_liga_ligateam', 'a');
      $query ->addExpression('count(idligateam)', 'anzahl');
      $query ->condition('idliga', $liga->idliga, '=');
      $result1 = $query->execute();
      $data = $result1->fetchObject();
      $anzteams = $data->anzahl;
      $form[$liga->idliga] = array(
          '#size' => '30',
          '#type' => 'link',
          //'#autocomplete_path' => 'liga/ligarights/name/autocomplete',
          '#title' => check_plain($liga->idliga . ' = ' . $liga->name),
          '#href' => 'liga/result/edit/' . $liga->idliga,
          '#maxlength' => 60,
          '#required' => FALSE,
          '#disabled' => TRUE,
          '#prefix' => '<tr><td>',
          '#suffix' => '</td>',
      );
      $form[$liga->idliga . '_teams'] = array(
          '#size' => '1',
          '#type' => 'textfield',
          //'#autocomplete_path' => 'liga/ligarights/name/autocomplete',
          '#default_value' => $anzteams,
          '#maxlength' => 1,
          '#required' => False,
          '#disabled' => TRUE,
          '#prefix' => '<td>',
          '#suffix' => '</td>',
      );
      $form[$liga->idliga . '_aufsteiger'] = array(
          '#size' => '1',
          '#type' => 'textfield',
          //'#autocomplete_path' => 'liga/ligarights/name/autocomplete',
          '#default_value' => $liga->aufsteiger,
          '#maxlength' => 1,
          '#required' => False,
          '#rules' => array(array('rule' => 'digit', 'error' => $liga->aufsteiger . ' : Es sind nur numerische Werte erlaubt.'), ),
          '#prefix' => '<td>',
          '#suffix' => '</td>',
      );
      $form[$liga->idliga . '_absteiger'] = array(
          '#size' => '1',
          '#type' => 'textfield',
          //'#autocomplete_path' => 'liga/ligarights/name/autocomplete',
          '#default_value' => $liga->absteiger,
          '#maxlength' => 2,
          '#required' => False,
          '#rules' => array(array('rule' => 'digit', 'error' => $liga->absteiger . ' : Es sind nur numerische Werte erlaubt.'), ),
          '#prefix' => '<td>',
          '#suffix' => '</td>',
      );
      $form[$liga->idliga . '_anz1'] = array(
          '#size' => '1',
          '#type' => 'textfield',
          '#disabled' => TRUE,
          '#default_value' => $beganz['1'] . ' / ' . $anzgemeldet['1'],
          '#prefix' => '<td>',
          '#suffix' => '</td>',
      );
      $form[$liga->idliga . '_anz2'] = array(
          '#size' => '1',
          '#type' => 'textfield',
          '#disabled' => TRUE,
          '#default_value' => $beganz['2'] . ' / ' . $anzgemeldet['2'],
          '#prefix' => '<td>',
          '#suffix' => '</td>',
      );
      $form[$liga->idliga . '_anz3'] = array(
          '#size' => '1',
          '#type' => 'textfield',
          '#disabled' => TRUE,
          '#default_value' => $beganz['3'] . ' / ' . $anzgemeldet['3'],
          '#prefix' => '<td>',
          '#suffix' => '</td>',
      );
      $form[$liga->idliga . '_anz4'] = array(
          '#size' => '1',
          '#type' => 'textfield',
          '#disabled' => TRUE,
          '#default_value' => isset($beganz['4']) ? $beganz['4'] . ' / ' . $anzgemeldet['4'] : '',
          '#prefix' => '<td>',
          '#suffix' => '</td>',
      );
      $form[$liga->idliga . '_freigabe'] = array(
          '#type' => 'checkbox',
          '#default_value' => $liga->freigabe,
          '#prefix' => '<td>',
          '#suffix' => '</td></tr>',
      );
    }
    $form['lastrow'] = array(
        '#markup' => '</table>',
    );
    $form['#prefix'] = 'Das aktuelle Ligajahr ist ' . $ligajahr . '</br>Folgende Ligen sind angelegt:</br>';
  } 
  else {
    $form = 'Es sind keine Ligen definiert.';
  }
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Save'),
  );
  /*$form['actions']['delete'] = array(
   '#type' => 'button',
      '#value' => t('Delete'),
  );
  $form['actions']['cancel'] = array(
      '#type' => 'button',
      '#value' => t('Cancel'),
  );*/
  return $form;
}

/**
 * Validierung für das Ligaadminformular
 * 
 * @param array $form
 *        Das Formular
 * @param array $form_state
 *        Die Werte des Formulars
 */
function npv_liga_admin_form_validate($form, &$form_state) {
  $query = db_select('npv_liga_liga', 'a');
  $query  ->addExpression('MAX(jahr)', 'jahraktuell');
  $query ->fields('a');
  $result = $query->execute();
  $data = $result->fetchObject();
  if ($data !== FALSE) {
    $ligajahr = $data->jahraktuell;
  } 
  else {
    form_set_error('', 'Keine Daten vorhanden.');
  }

  $query = db_select('npv_liga_liga', 'a');
  $query ->fields('a');
  $query ->condition('jahr', $ligajahr, '=');
  $query ->orderBy('idliga');
  $result = $query->execute();
  if ($result !== FALSE) {
    foreach ($result as $liga) {
      $query = db_select('npv_liga_ligateam', 'a');
      $query ->addExpression('count(idligateam)', 'anzahl');
      $query ->condition('idliga', $liga->idliga, '=');
      $result1 = $query->execute();
      $data = $result1->fetchObject();
      if ($form_state['values'][$liga->idliga . '_aufsteiger'] < 0 || $form_state['values'][$liga->idliga . '_aufsteiger'] > $data->anzahl) {
        form_set_error($liga->idliga . '_aufsteiger', $liga->idliga . ':' . $liga->name . ' - Es kann nur keinen, einen, oder maximal ' . $data->anzahl . ' Aufsteiger geben.');
      }
      if ($form_state['values'][$liga->idliga . '_absteiger'] < 0 || $form_state['values'][$liga->idliga . '_absteiger'] <= $form_state['values'][$liga->idliga . '_aufsteiger']) {
        form_set_error($liga->idliga . '_absteiger', $liga->idliga . ':' . $liga->name . ' - Absteiger kann es erst ab Platz ' . ($form_state['values'][$liga->idliga . '_aufsteiger'] + 1) . ' geben.');
      }
    }
  }
}

function npv_liga_admin_form_submit($form, &$form_state) {
  $query = db_select('npv_liga_liga', 'a');
  $query  ->addExpression('MAX(jahr)', 'jahraktuell');
  $query ->fields('a');
  $result = $query->execute();
  $data = $result->fetchObject();
  if ($data !== FALSE) {
    $ligajahr = $data->jahraktuell;
  } 
  else {
    form_set_error('', 'Keine Daten vorhanden.');
    return FALSE;
  }
  $query = db_select('npv_liga_liga', 'a');
  $query ->fields('a');
  $query ->condition('jahr', $ligajahr, '=');
  $query ->orderBy('idliga');
  $result = $query->execute();
  if ($result !== FALSE) {
    foreach ($result as $liga) {
      db_merge('npv_liga_liga')
      ->key(array('idliga' => $liga->idliga))
      ->fields(array(
          'date_ame' => REQUEST_TIME,
          'aufsteiger' => $form_state['values'][$liga->idliga . '_aufsteiger'],
          'absteiger' => $form_state['values'][$liga->idliga . '_absteiger'],
          'freigabe' => $form_state['values'][$liga->idliga . '_freigabe'],
      ))
      ->execute();
    }
  }
}

/* interne Hilfsroutinen */

/**
 * Liefert alle Ligen des aktuellen Ligajahres
 * 
 * @return array Ligen des aktuellen Ligajahres.
 */
function _npv_liga_get_liga_array() {
  $ligen = array();
  $query = db_select('npv_liga_liga', 'a');
  $query  ->addExpression('MAX(jahr)', 'jahraktuell');
  $result = $query->execute();
  $data = $result->fetchAssoc();
  if ($data !== FALSE) {
    $query = db_select('npv_liga_liga', 'a');
    $query ->condition('jahr', $data['jahraktuell'], '=');
    $query ->fields('a', array('idliga', 'name'));
    $query ->orderBy('idliga', 'ASC');
    $result = $query ->execute();
    foreach ($result as $row) {
      $ligen[] = (array) $row;
    }
  }
  return $ligen;
}

/**
 * Liefert die Eingaben der aktivierten Checkboxen des Rechteformulars
 * in einem Semikolon-separierten String.
 * 
 * @param  array $form_state
 *         Formulareingaben
 * @return string
 */
function _npv_liga_get_melderechte_string_from_form($form_state) {
  $melderechte = '';
  foreach ($form_state['values']['melderechte'] as $recht) {
    if ($recht !== 0) {
      $melderechte .= $recht . ';';
    }
  }
  if (strlen($melderechte) !== 0) {
    $melderechte = substr($melderechte, 0, strlen($melderechte)-1);
  }
  return $melderechte;
}