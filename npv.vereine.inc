<?php
// $Id$
/**
 * @file
 * Functions for managing clubs
 */

function npv_vereine_admin() {
  $headers= array(
    array('data' =>  t('Vereins ID'), 'field' => 'idvereine', 'sort' => 'asc', ),
    array('data' =>  t('Name'), 'field' => 'name', 'sort' => 'asc', ),
    array('data' =>  t('Ort'), 'field' => 'ort', ),
    array('data' =>  t('Lizenznummer'), 'field' => 'lizenznr', ),
    array('data' => t('Bearbeiter'), 'field' => 'username', ),
    array('data' => t('letzte Änderung'), 'field' => 'date_last_change', ),
    array('data' => t('Operation'), 'field' => 'operation')
  );

  $rows = array();

  $query = npv_vereine_build_filter_query();
  $query ->orderByHeader($headers);
  $result = $query
  ->limit(20) // Number of records (or nodes, in our case) to show per page.
  ->execute();

  foreach ($result as $row) {
    $arow = array();
    $arow['idvereine'] = $row->idvereine;
    $arow['name'] = $row->name;
    $arow['ort'] = $row->ort;
    $arow['lizenznr'] = $row->lizenznr;
    $arow['username'] = $row->username;
    $arow['date_last_change'] = !empty($row->date_last_change) ? format_date($row->date_last_change, 'short') : 'ohne'; 
    $arow['operation'] = '<ul class="links inline">';
    $arow['operation'] .= '<li class="edit first">'.l(t('Edit'), 'admin/npv/vereine/edit/' . $row->idvereine).'</li>';
    $arow['operation'] .= '<li class="delete">'.l(t('Delete'), 'admin/npv/vereine/edit/' . $row->idvereine).'</li>';
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

  // Return the output with the pager attached to it.  The pager
  // is the box underneath the table that allows people to jump
  // to the next page.
  
  //$build['pager_pager'] = array('#theme' => 'pager');
  return $build;

}

function npv_vereine_add_form($form, $form_state, $op = 'new', $id = 0) {
  $form = array();
  if ($op == 'edit') {
    $result = db_select('npv_vereine', 'a')
       ->fields('a')
       ->condition('idvereine', $id)
       ->execute();
    $record = $result->fetchObject();
    $form['aktion'] = array('#type' => 'hidden', '#value' => 'edit');
    $form['idvereine'] = array('#type' => 'hidden', '#value' => $id);
  }
  $form['name'] = array(
    '#size' => '60',
    '#weight' => '0',
    '#type' => 'textfield',
    '#title' => 'Name',
    '#default_value' => isset($record->name) ? $record->name : '',
    '#maxlength' => 100,
    '#description' => 'Der Name des Vereins.',
    '#required' => TRUE,
  );
  $form['ort'] = array(
    '#size' => '60',
    '#weight' => '1',
    '#type' => 'textfield',
    '#title' => 'Ort',
    '#default_value' => isset($record->ort) ? $record->ort : '',
    '#maxlength' => 100,
    '#description' => 'Der Ort des Vereins.',
    '#required' => TRUE,
  );
  $form['lizenznr'] = array(
    '#size' => '60',
    '#weight' => '2',
    '#type' => 'textfield',
    '#title' => 'Lizenz-Nr.',
    '#default_value' => isset($record->lizenznr) ? $record->lizenznr : '',
    '#maxlength' => 7,
    '#description' => 'Die Lizenz-Nummer des Vereins inklusive der Verbandsnummer.',
    '#required' => TRUE,
  );
  $form['website'] = array(
    '#size' => '60',
    '#weight' => '3',
    '#type' => 'textfield',
    '#title' => 'Homepage',
    '#default_value' => isset($record->website) ? $record->website : '',
    '#maxlength' => 45,
    '#description' => 'Die Homepage des Vereins.',
    '#required' => FALSE,
  );
  $form['kontakt'] = array(
    '#type' => 'fieldset',
    '#weight' => '4',
    '#title' => t('Kontaktanschrift'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['kontakt']['anschrift'] = array(
    '#size' => '60',
    '#weight' => '5',
    '#rows' => '6',
    '#wysiwyg' => FALSE,
    '#type' => 'textarea',
    '#title' => 'Anschrift',
    '#default_value' => isset($record->anschrift) ? $record->anschrift : '',
    '#maxlength' => 500,
    '#description' => 'Die Anschrift des Vereins.',
    '#required' => FALSE,
  );
  $form['kontakt']['telefon'] = array(
    '#size' => '60',
    '#weight' => '6',
    '#type' => 'textfield',
    '#title' => 'Telefon',
    '#default_value' => isset($record->telefon) ? $record->telefon : '',
    '#maxlength' => 100,
    '#description' => 'Die Telefonnummer für die Anschrift des Vereins.',
    '#required' => FALSE,
  );
  $form['kontakt']['fax'] = array(
    '#size' => '60',
    '#weight' => '7',
    '#type' => 'textfield',
    '#title' => 'Fax',
    '#default_value' => isset($record->fax) ? $record->fax : '',
    '#maxlength' => 100,
    '#description' => 'Die Faxnummer für die Anschrift des Vereins.',
    '#required' => FALSE,
  );
  $form['kontakt']['sportbund'] = array(
    '#size' => '60',
    '#weight' => '8',
    '#type' => 'textfield',
    '#autocomplete_path' => 'sportbund/autocomplete',
    '#title' => 'Sportbund',
    '#default_value' => isset($record->sportbund) ? $record->sportbund : '',
    '#maxlength' => 100,
    '#description' => 'Der Sportbund des Vereins.',
    '#required' => FALSE,
  );
  $form['kontakt']['email'] = array(
    '#size' => '60',
    '#weight' => '9',
    '#rows' => '3',
    '#wysiwyg' => FALSE,
    '#type' => 'textarea',
    '#title' => 'E-mail',
    '#default_value' => isset($record->email) ? $record->email : '',
    '#maxlength' => 200,
    '#description' => 'Die E-mail Anscchrift des Vereins.',
    '#required' => FALSE,
  );
  $form['boule'] = array(
    '#type' => 'fieldset',
    '#weight' => '10',
    '#title' => t('Boulodrome'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['boule']['boulodrome'] = array(
    '#size' => '60',
    '#weight' => '11',
    '#rows' => '3',
    '#wysiwyg' => FALSE,
    '#type' => 'textarea',
    '#title' => 'Boulodrôme',
    '#default_value' => isset($record->boulodrome) ? $record->boulodrome : '',
    '#maxlength' => 200,
    '#description' => 'Das Boulodrôme des Vereins.',
    '#required' => FALSE,
  );
  $form['boule']['latitude'] = array(
    '#size' => '60',
    '#weight' => '12',
    '#type' => 'textfield',
    '#title' => t('Latitude'),
    '#default_value' => isset($record->latitude) ? $record->latitude : '',
    '#maxlength' => 100,
    '#description' => 'Der Breitengrad für den Standort des Boulodrômes.',
    '#required' => FALSE,
  );
  $form['boule']['longitude'] = array(
    '#size' => '60',
    '#weight' => '13',
    '#type' => 'textfield',
    '#title' => t('Longitude'),
    '#default_value' => isset($record->longitude) ? $record->longitude : '',
    '#maxlength' => 100,
    '#description' => 'Der Längengrad für den Standort des Boulodrômes.',
    '#required' => FALSE,
  );
  $form['date_last_change'] = array(
    '#size' => '60',
    '#weight' => '14',
    '#type' => 'textfield',
    '#title' => 'Letzte Änderung',
    '#default_value' => isset($record->date_last_change) ? format_date($record->date_last_change) : '',
    '#maxlength' => 45,
    '#description' => 'Die letzte Änderung dies Datensatzes.',
    '#disabled' => TRUE,
    '#required' => FALSE,
  );
  $form['del_yn'] = array(
    '#weight' => '12',
    '#type' => 'checkbox',
    '#title' => 'gelöscht',
    '#default_value' => isset($record->del_yn) ? $record->del_yn : 0,
    '#required' => FALSE,
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
  return $form;
}


function npv_vereine_add() {
  return drupal_get_form('npv_vereine_add_form');
}


function npv_vereine_add_form_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Cancel')) {
    drupal_get_messages('error');
    drupal_goto('admin/npv/vereine');
  }
  // lizenznr
  $lic = $form_state['values']['lizenznr'];
  if (strlen($lic) == 7) {
    $licnpv = substr($lic, 0, 3);
    $licz = substr($lic, 3, 1);
    $licverein = substr($lic, 4, 3);
    if (ctype_digit($licnpv) && ctype_digit($licverein) && $licz == '-') {
      if (!isset($form_state['values']['aktion'])) {
        $query = db_select('npv_vereine', 'a')
          ->fields('a')
          ->condition('lizenznr', isset($form_state['values']['lizenznr']) ? $form_state['values']['lizenznr'] : 0);
        $result = $query
        ->execute();

        if ($result->rowCount() > 0) {
          $record = $result->fetchObject();
          form_set_error("lizenznr", "Es existiert bereits der Verein " . $record->name . " unter der Lizenz-Nr. " . $lic);
          $ret = FALSE;
        }
      }
    }
  }
  else {
    form_set_error('lizenznr', 'Das Format für die Lizenznummer ist falsch!');
  }
  // latitude und longitude
  if (!empty($form_state['values']['latitude'])) {
    $decimal = '.';
    $start = $form_state['values']['latitude'];
    $value = preg_replace('@[^-0-9\\' . $decimal . ']@', '', $form_state['values']['latitude']);
    if ($start != $value) {
      form_set_error("latitude", t('Es sind nur Nummern (0-9) und das Dezimalzeichen (.) in geogr. Breite erlaubt.'));
      $ret = FALSE;
    }
  }
  if (!empty($form_state['values']['longitude'])) {
    $decimal = '.';
    $start = $form_state['values']['longitude'];
    $value = preg_replace('@[^-0-9\\' . $decimal . ']@', '', $form_state['values']['longitude']);
    if ($start != $value) {
      form_set_error("longitude", t('Es sind nur Nummern (0-9) und das Dezimalzeichen (.) in geogr. Länge erlaubt.'));
      $ret = FALSE;
    }
  }
}


function npv_vereine_add_form_submit($form, &$form_state) {
  global $user;
  // Geocoden der Boulodromeanschrift
  if (isset($form_state['values']['boulodrome']) && (empty($form_state['values']['latitude']) || empty($form_state['values']['longitude']))) {
    $point = geocoder('google',$form_state['values']['boulodrome']);    
    if(isset($point->coords['0'])) {
      $form_state['values']['latitude'] = $point->coords['0'];
      $form_state['values']['longitude'] = $point->coords['1'];
    }
  }
  
  $values = array('idvereine' => isset($form_state['values']['idvereine']) ? $form_state['values']['idvereine'] : 0,
      'name' => $form_state['values']['name'],
      'ort' => $form_state['values']['ort'],
      'lizenznr' => $form_state['values']['lizenznr'],
      'website' => $form_state['values']['website'],
      'anschrift' => $form_state['values']['anschrift'],
      'telefon' => $form_state['values']['telefon'],
      'fax' => $form_state['values']['fax'],
      'sportbund' => $form_state['values']['sportbund'],
      'email' => $form_state['values']['email'],
      'boulodrome' => $form_state['values']['boulodrome'],
      'latitude' => isset($form_state['values']['latitude']) && !empty($form_state['values']['latitude']) ? $form_state['values']['latitude'] : 0,
      'longitude' => isset($form_state['values']['longitude']) && !empty($form_state['values']['longitude']) ? $form_state['values']['longitude'] : 0,
      'del_yn' => $form_state['values']['del_yn'],
      'uid' => $user->uid,
  );
  if (isset($form_state['values']['aktion'])) {
    $sql = 'INSERT INTO npv_vereine_hist (idvereine, name, ort, lizenznr, website, anschrift, telefon, ';
    $sql .= 'fax, sportbund, email, boulodrome, latitude, longitude, date_last_change, date_created, ';
    $sql .= 'del_yn, uid) SELECT * FROM npv_vereine a WHERE a.idvereine = :idvereine';
    $result = db_query($sql, array(':idvereine' => $form_state['values']['idvereine']));
    $values['date_last_change'] = time();
    if (drupal_write_record('npv_vereine', $values, 'idvereine')) {
      drupal_set_message(check_plain('Die Daten des Vereins ' . $values['name'] . ' wurden erfolgreich aktualisiert!'));
      drupal_goto('admin/npv/vereine');
    }
    else {
      drupal_set_message(check_plain('Die Daten des Vereins ' . $values['name'] . ' konnten aufgrund eines Datenbankproblems nicht aktualisiert werden!'), 'error');
    }
  }
  else {
    $values['date_last_change'] = time();
    $values['date_created'] = time();
    
    if (drupal_write_record('npv_vereine', $values)) {
      drupal_set_message(check_plain('Der Verein ' . $values['name'] . ' wurde erfolgreich angelegt!'));
      drupal_goto('admin/npv/vereine');
    }
    else {
      drupal_set_message(check_plain('Der Verein ' . $values['name'] . ' aufgrund eines Datenbankproblems nicht angelegt werden!'), 'error');
    }
  }
}


function npv_vereine_edit($id) {
  return drupal_get_form('npv_vereine_add_form', 'edit', $id);
}


function export_vereine_excel_csv() {
  // Prevent Devel from messing us up.
  $GLOBALS['devel_shutdown'] = TRUE;
  
  // Set the headers to indicate this is a CSV file.
  header('Content-type: text/csv; charset=UTF-8');
  header('Content-Disposition: attachment; filename=npv_vereine.csv');
  header('Pragma: no-cache');
  header('Expires: 0');

  // Create a file.
  $output = fopen('php://output', 'w');

  // Column names.
  //fputcsv ($output, array('ID', 'Name', 'Ort', 'Lizenznummer', 'Bearbeiter', 'Letzte Änderung'),';','"');
  fputs($output, '"ID";"Name";"Ort";"Lizenznummer";"Bearbeiter";"Letzte Änderung"'.chr(13).chr(10));
  $query = db_select('npv_vereine', 'a');
  $query  ->fields('a', array('idvereine', 'name', 'ort', 'lizenznr', 'website', 'date_last_change' ));
  $result = $query ->execute();

  // Loop through the rows.
  foreach ($result as $row) {
    
    fputcsv($output, (array) $row, ';','"');
  }

  fclose($output);
}
/**
 * Menu callback: Spieler Verwaltung.
 */
function npv_vereine_admin_form($form, $form_state) {

  $form['filter'] = npv_vereine_filter_form();
  $form['#submit'][] = 'npv_vereine_filter_form_submit';
  $form['admin'] = npv_vereine_admin();

  $form['pager'] = array('#markup' => theme('pager'));
  return $form;
}

function npv_vereine_filter_form_submit($form, $form_state) {
  switch ($form_state['values']['op']) {
    case t('Filter'):
    case t('Refine'):
      unset($_SESSION['npv_vereine_filter']);
      if (isset($form_state['values']['lizenzfilter']) && !empty($form_state['values']['lizenzfilter'])) {
        $_SESSION['npv_vereine_filter'][] = array('lizenz', $form_state['values']['lizenz'], $form_state['values']['lizenzfilter']);
      }
      if (isset($form_state['values']['namefilter']) && !empty($form_state['values']['namefilter'])) {
        $_SESSION['npv_vereine_filter'][] = array('name', $form_state['values']['name'], $form_state['values']['namefilter']);
      }
      if (isset($form_state['values']['ortfilter']) && !empty($form_state['values']['ortfilter'])) {
        $_SESSION['npv_vereine_filter'][] = array('ort', $form_state['values']['ort'], $form_state['values']['ortfilter']);
      }
      break;
  }
}

function npv_vereine_filter_form() {
  $filteroptions = array('Ist gleich' => 'Ist gleich',
    'Ist nicht gleich' => 'Ist nicht gleich',
    'Beginnt mit' => 'Beginnt mit',
    'Beginnt nicht mit' => 'Beginnt nicht mit',
    'Enthält' => 'Enthält',
    'Enthält nicht' => 'Enthält nicht',
    'Endet mit' => 'Endet mit',
    'Endet nicht mit' => 'Endet nicht mit',
  );

  $filters = isset($_SESSION['npv_vereine_filter']) ? $_SESSION['npv_vereine_filter'] : array();

  foreach ($filters as $filt) {
    switch ($filt['0']) {
      case 'lizenz':
        $filter['lizenz']['op'] = $filt['1'];
        $filter['lizenz']['value'] = $filt['2'];
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

  // Lizenz
  $form['filters']['status']['filters']['lizenz'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('filterfilters')),
  );
  $form['filters']['status']['filters']['lizenz']['lizenz'] = array(
    '#type' => 'select',
    '#options' => $filteroptions,
    '#title' => 'Lizenz',
    '#default_value' => isset($filter['lizenz']['op']) ? $filter['lizenz']['op'] : 'Enthält',
  );
  $form['filters']['status']['filters']['lizenz']['lizenzfilter'] = array(
    '#type' => 'textfield',
    '#size' => '60',
    '#maxlength' => 45,
    '#default_value' => isset($filter['lizenz']['value']) ? $filter['lizenz']['value'] : '',
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
function npv_vereine_build_filter_query() {
  // Build query

  $query = db_select('npv_vereine', 'a')->extend('PagerDefault')->extend('TableSort');
  $query  ->fields('a', array('idvereine', 'name', 'ort', 'lizenznr', 'date_last_change' ));
  $query  ->join('users', 'b', 'a.uid = b.uid');
  $query  ->addfield('b', 'name', 'username');
  
  $filter_data = isset($_SESSION['npv_vereine_filter']) ? $_SESSION['npv_vereine_filter'] : array();

  foreach ($filter_data as $filter) {
    switch ($filter['0']) {
      case 'lizenz':
        $query->condition('a.lizenznr', _npv_get_vereinsfilter($filter['2'], $filter['1']), _npv_get_vereinsfilteroperator($filter['1']));
        break;
      case 'name':
        $query->condition('a.name', _npv_get_vereinsfilter($filter['2'], $filter['1']), _npv_get_vereinsfilteroperator($filter['1']));
        break;
      case 'ort':
        $query->condition('a.ort', _npv_get_vereinsfilter($filter['2'], $filter['1']), _npv_get_vereinsfilteroperator($filter['1']));
        break;
    }
  }
  return $query;
}

function _npv_get_vereinsfilteroperator($filter) {
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

function _npv_get_vereinsfilter($filter, $filteroperator) {
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