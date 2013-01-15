<?php
// $Id$
/**
 * @file
 * Function to make tables visible to views module
 */

function npv_views_tables() {
  $table = array(
    'name' => 'npv_vereine',
    //more...
  );
  $tables["npv_vereine"] = $table;

  return $tables;
}

function npv_views_data() {
  // The 'group' index will be used as a prefix in the UI for any of this
  // table's fields, sort criteria, etc. so it's easy to tell where they came
  // from.
  $data['npv_vereine']['table']['group'] = t('NPV Vereine');

  // Define this as a base table.
  $data['npv_vereine']['table']['base'] = array(
    'field' => 'idvereine',
    'title' => t('NPV - Vereine'),
    'help' => t("Alle Vereine des NPV."),
    'weight' => -10,
  );

  // Next, describe each of the individual fields in this table to Views. For
  // each field, you may define what field, sort, argument, and/or filter
  // handlers it supports. This will determine where in the Views interface you
  // may use the field.

  // idvereine.
  $data['npv_vereine']['idvereine'] = array(
    'title' => t('Interne ID des Vereins'),
    'help' => t('Interne ID des Vereins'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
   );

   // name.
   $data['npv_vereine']['name'] = array(
     'title' => t('Name'),
     'help' => t('Der Name des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // ort.
   $data['npv_vereine']['ort'] = array(
     'title' => t('Ort'),
     'help' => t('Der Ort des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // lizenznr.
   $data['npv_vereine']['lizenznr'] = array(
     'title' => t('Lizenz-Nummer'),
     'help' => t('Die Lizenz-Nummer des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // website.
   $data['npv_vereine']['website'] = array(
     'title' => t('Website'),
     'help' => t('Die Website des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // anschrift.
   $data['npv_vereine']['anschrift'] = array(
     'title' => t('Anschrift'),
     'help' => t('Die Anschrift des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // telefon.
   $data['npv_vereine']['telefon'] = array(
     'title' => t('Telefon'),
     'help' => t('Die Telefon-Nummer des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );


   // boulodrome.
   $data['npv_vereine']['boulodrome'] = array(
     'title' => t('Boulodrôme'),
     'help' => t('Das Boulodrôme des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );
   //Länge
   $data['npv_vereine']['latitude'] = array(
     'title' => t('Latitude'),
     'help' => t('Latitude.'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );
   //Breite
   $data['npv_vereine']['longitude'] = array(
     'title' => t('Longitude'),
     'help' => t('Longitude.'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );
   $data['npv_vereine']['table']['group'] = t('NPV Vereine');

   // Define this as a base table.
   $data['npv_vereine']['table']['base'] = array(
     'field' => 'idvereine',
     'title' => t('NPV - Vereine'),
     'help' => t("Alle Vereine des NPV."),
     'weight' => -10,
   );

   // Next, describe each of the individual fields in this table to Views. For
   // each field, you may define what field, sort, argument, and/or filter
   // handlers it supports. This will determine where in the Views interface you
   // may use the field.

   // idvereine.
   $data['npv_vereine']['idvereine'] = array(
     'title' => t('Interne ID des Vereins'),
     'help' => t('Interne ID des Vereins'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // name.
   $data['npv_vereine']['name'] = array(
     'title' => t('Name'),
     'help' => t('Der Name des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // ort.
   $data['npv_vereine']['ort'] = array(
     'title' => t('Ort'),
     'help' => t('Der Ort des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // lizenznr.
   $data['npv_vereine']['lizenznr'] = array(
     'title' => t('Lizenz-Nummer'),
     'help' => t('Die Lizenz-Nummer des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // website.
   $data['npv_vereine']['website'] = array(
     'title' => t('Website'),
     'help' => t('Die Website des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // anschrift.
   $data['npv_vereine']['anschrift'] = array(
     'title' => t('Anschrift'),
     'help' => t('Die Anschrift des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // telefon.
   $data['npv_vereine']['telefon'] = array(
     'title' => t('Telefon'),
     'help' => t('Die Telefon-Nummer des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );


   // boulodrome.
   $data['npv_vereine']['boulodrome'] = array(
     'title' => t('Boulodrôme'),
     'help' => t('Das Boulodrôme des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );
   //Länge
   $data['npv_vereine']['latitude'] = array(
     'title' => t('Latitude'),
     'help' => t('Latitude.'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );
   //gelöscht
   $data['npv_vereine']['del_yn'] = array(
     'title' => t('gelöscht'),
     'help' => t('gelöscht.'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );
   
   $data['npv_vereine']['table']['join'] = array(
  // Index this array by the table name to which this table refers.
  // 'left_field' is the primary key in the referenced table.
  // 'field' is the foreign key in this table.
      'npv_vereine_hist' => array(
          'left_field' => 'idvereine',
          'field' => 'idvereine',
      ),
  );
   // Example plain text field.
   /*
   $data['npv_vereine']['plain_text_field'] = array(
     'title' => t('Plain text field'),
     'help' => t('Just a plain text field.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );
 */

   // Example numeric text field.
   /*
   $data['example_table']['numeric_field'] = array(
     'title' => t('Numeric field'),
     'help' => t('Just a numeric field.'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );
 */

   // Example boolean field.
   /*
   $data['example_table']['boolean_field'] = array(
     'title' => t('Boolean field'),
     'help' => t('Just an on/off field.'),
     'field' => array(
       'handler' => 'views_handler_field_boolean',
       'click sortable' => TRUE,
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_boolean_operator',
       'label' => t('Published'),
       'type' => 'yes-no',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );
 */

   // Example timestamp field.
   /*
   $data['example_table']['timestamp_field'] = array(
     'title' => t('Timestamp field'),
     'help' => t('Just a timestamp field.'),
     'field' => array(
       'handler' => 'views_handler_field_date',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort_date',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_date',
     ),
   );
 */

  /* Definition für Historientabelle der Vereine */
  $data['npv_vereine_hist']['table']['group'] = t('NPV Vereinshistorie');

   // Define this as a base table.
   $data['npv_vereine_hist']['table']['base'] = array(
     'field' => 'idvereine',
     'title' => t('Historie der NPV - Vereine'),
     'help' => t("Historie der Vereine des NPV."),
     'weight' => -10,
   );

   // Next, describe each of the individual fields in this table to Views. For
   // each field, you may define what field, sort, argument, and/or filter
   // handlers it supports. This will determine where in the Views interface you
   // may use the field.

   // idvereine.
   $data['npv_vereine_hist']['hid'] = array(
     'title' => t('ID Nummer des Historieneintrags'),
     'help' => t('ID Nummer des Historieneintrags'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );
   
   // idvereine.
   $data['npv_vereine_hist']['idvereine'] = array(
     'title' => t('Interne ID des Vereins'),
     'help' => t('Interne ID des Vereins'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // name.
   $data['npv_vereine_hist']['name'] = array(
     'title' => t('Name'),
     'help' => t('Der Name des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // ort.
   $data['npv_vereine_hist']['ort'] = array(
     'title' => t('Ort'),
     'help' => t('Der Ort des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // lizenznr.
   $data['npv_vereine_hist']['lizenznr'] = array(
     'title' => t('Lizenz-Nummer'),
     'help' => t('Die Lizenz-Nummer des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // website.
   $data['npv_vereine_hist']['website'] = array(
     'title' => t('Website'),
     'help' => t('Die Website des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // anschrift.
   $data['npv_vereine_hist']['anschrift'] = array(
     'title' => t('Anschrift'),
     'help' => t('Die Anschrift des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );

   // telefon.
   $data['npv_vereine_hist']['telefon'] = array(
     'title' => t('Telefon'),
     'help' => t('Die Telefon-Nummer des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );


   // boulodrome.
   $data['npv_vereine_hist']['boulodrome'] = array(
     'title' => t('Boulodrôme'),
     'help' => t('Das Boulodrôme des Vereins.'),
     'field' => array(
       'handler' => 'views_handler_field',
       'click sortable' => TRUE,
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
     'filter' => array(
       'handler' => 'views_handler_filter_string',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_string',
     ),
   );
   //Länge
   $data['npv_vereine_hist']['latitude'] = array(
     'title' => t('Latitude'),
     'help' => t('Latitude.'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );
   //Breite
   $data['npv_vereine_hist']['longitude'] = array(
     'title' => t('Longitude'),
     'help' => t('Longitude.'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );
    //gelöscht
   $data['npv_vereine_hist']['del_yn'] = array(
     'title' => t('gelöscht'),
     'help' => t('gelöscht.'),
     'field' => array(
       'handler' => 'views_handler_field_numeric',
       'click sortable' => TRUE,
      ),
     'filter' => array(
       'handler' => 'views_handler_filter_numeric',
     ),
     'sort' => array(
       'handler' => 'views_handler_sort',
     ),
   );
   
  return $data;
 }