<?php
/**
 * @file 
 * Funktionen für den Import der NPV-Ranglisten als CSV-Datei.
 * 
 * Die Dateien müssen im Format UTF-8 ohne BOM vorliegen.
 */

/**
 * Menüaufruf zur Anzeige des Upload-Formulars zum Importieren der Ranglisten
 * 
 * @return array Eingabeformular
 */
function npv_rangliste_import() {
  $page_array['npv_ranglisten_import'] = array(
  //Title serves as page subtitle
    '#title' => t('All posts from the last week'),
    '#markup' => t('No posts available.'),
  );
  //return $page_array;
  return drupal_get_form('npv_rangliste_import_form');
}

function npv_rangliste_import_form($form_state) {
  // If you are familiar with how browsers handle files, you know that
  // enctype="multipart/form-data" is required. Drupal takes care of that, so
  // you don't need to include it yourself.

  $form['file_einzel'] = array(
      '#type' => 'file',
      '#title' => t('Rangliste Einzel'),
      '#description' => t('Ranglistenimport-Datei für Einzelübersicht.'),
  );
  $form['file_event'] = array(
      '#type' => 'file',
      '#title' => t('Ranglisten Events'),
      '#description' => t('Ranglistenimport-Datei für Events.'),
  );
  $form['file_verein'] = array(
      '#type' => 'file',
      '#title' => t('Ranglisten Verein'),
      '#description' => t('Ranglistenimport-Datei für Vereinsübersicht.'),
  );
  $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Submit'),
  );

  return $form;
}

/**
 * Validate handler for form_example_tutorial_10().
 */
function npv_rangliste_import_form_validate($form, &$form_state) {
  $file = file_save_upload('file_einzel', array(
      'file_validate_extensions' => array('csv'), // Validate extensions.
  ));
  // If the file passed validation:
  if ($file) {
    // Move the file, into the Drupal file system
    if ($file = file_move($file, 'public://import', FILE_EXISTS_REPLACE)) {
      // Save the file for use in the submit handler.
      $form_state['storage']['file_einzel'] = $file;
    }
    else {
      form_set_error('file_einzel', t('Failed to write the uploaded file the site\'s file folder.'));
    }
  } 
  else {
    $form_state['storage']['file_einzel'] = FALSE;
  }
  $file = file_save_upload('file_event', array(
      'file_validate_extensions' => array('csv'), // Validate extensions.
  ));
  // If the file passed validation:
  if ($file) {
    // Move the file, into the Drupal file system
    if ($file = file_move($file, 'public://import', FILE_EXISTS_REPLACE)) {
      // Save the file for use in the submit handler.
      $form_state['storage']['file_event'] = $file;
    }
    else {
      form_set_error('file_event', t('Failed to write the uploaded file the site\'s file folder.'));
    }
  } 
  else {
    $form_state['storage']['file_event'] = FALSE;
  }
  $file = file_save_upload('file_verein', array(
      'file_validate_extensions' => array('csv'), // Validate extensions.
  ));
  // If the file passed validation:
  if ($file) {
    // Move the file, into the Drupal file system
    if ($file = file_move($file, 'public://import', FILE_EXISTS_REPLACE)) {
      // Save the file for use in the submit handler.
      $form_state['storage']['file_verein'] = $file;
    }
    else {
      form_set_error('file_verein', t('Failed to write the uploaded file the site\'s file folder.'));
    }
  } 
  else {
    $form_state['storage']['file_verein'] = FALSE;
  }
}

/**
 * Submit handler for form_example_tutorial_10().
 */
function npv_rangliste_import_form_submit($form, &$form_state) {
  $fileeinzel = $form_state['storage']['file_einzel'];
  // We are done with the file, remove it from storage.
  unset($form_state['storage']['file_einzel']);
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
  $fileevent = $form_state['storage']['file_event'];
  // We are done with the file, remove it from storage.
  unset($form_state['storage']['file_event']);
  if ($fileevent) {
    // Make the storage of the file permanent
    $fileevent->status = FILE_STATUS_PERMANENT;
    // Save file status.
    file_save($fileevent);
    // Set a response to the user.
    $fileevent->destination = drupal_realpath('public://import/' . $fileevent->filename);
    drupal_set_message(t('Die Datei wurde hochgeladen und gespeichert, Dateiname: @filename.', array('@filename' => $fileevent->destination)));
  } 
  else {
    drupal_set_message(t('Es wurde keine Datei für die Events hochgeladen.'));
  }
  $fileverein = $form_state['storage']['file_verein'];
  // We are done with the file, remove it from storage.
  unset($form_state['storage']['file_verein']);
  if ($fileverein) {
    // Make the storage of the file permanent
    $fileverein->status = FILE_STATUS_PERMANENT;
    // Save file status.
    file_save($fileverein);
    // Set a response to the user.
    $fileverein->destination = drupal_realpath('public://import/' . $fileverein->filename);
    drupal_set_message(t('Die Datei wurde hochgeladen und gespeichert, Dateiname: @filename.', array('@filename' => $fileverein->destination)));
  } 
   else {
    drupal_set_message(t('Es wurde keine Datei für die Vereinsübersicht hochgeladen.'));
  }
  /* Verarbeitung der Daten
   */
  if ($fileeinzel) {
    include_once '' . drupal_get_path('module', 'npv') . '/csv.inc';
    csv_file_to_mysql_table(drupal_realpath('public://import/' . $fileeinzel->filename), 'npv_rl_einzel', IMPORT_TYPE_RLEINZEL);
  }
  if ($fileevent) {
    include_once '' . drupal_get_path('module', 'npv') . '/csv.inc';
    csv_file_to_mysql_table(drupal_realpath('public://import/' . $fileevent->filename), 'npv_rl_event', IMPORT_TYPE_RLEVENT);
  }
  if ($fileverein) {
    include_once '' . drupal_get_path('module', 'npv') . '/csv.inc';
    csv_file_to_mysql_table(drupal_realpath('public://import/' . $fileverein->filename), 'npv_rl_verein', IMPORT_TYPE_RLVEREIN);
  }
}