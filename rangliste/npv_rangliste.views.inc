<?php
/**
 * @file 
 * Views Integration für Modul NPV-Rangliste
 */

/**
 * Implements hook_views_data
 * 
 * @return array Datenstruktur für views-integration
 */
function npv_rangliste_views_data() {
  $data['npv_rl_einzel']['table'] = array(
    'group' => 'NPV Rangliste Einzel',
    'base' => array(
      'field' => array('LizNr'),
      'title' => 'NPV Rangliste Einzel',
      'help' => 'Tabelle für NPV Ranglisten Einzel.',
    ),
  );

  // Example plain text field.
  $data['npv_rl_einzel']['LizNr'] = array(
      'title' => t('Lizenz-Nr.'),
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
  $data['npv_rl_einzel']['VKennZif'] = array(
      'title' => t('VKennZif'),
      'help' => t('Vereinskennziffer.'),
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
  $data['npv_rl_einzel']['Spieler'] = array(
      'title' => t('Spieler'),
      'help' => t('Vollständiger Name des Spielers.'),
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
  // Example numeric text field.
  $data['npv_rl_einzel']['Alter'] = array(
    'title' => t('Alter'),
    'help' => t('Das Alter des Spielers in Jahren.'),
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
  $data['npv_rl_einzel']['Sex'] = array(
      'title' => t('Sex'),
      'help' => t('Geschlecht des Spielers.'),
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
  $data['npv_rl_einzel']['event01'] = array(
      'title' => t('1. Event'),
      'help' => t('Anzahl Punkte des 1. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event02'] = array(
      'title' => t('2. Event'),
      'help' => t('Anzahl Punkte des 2. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event03'] = array(
      'title' => t('3. Event'),
      'help' => t('Anzahl Punkte des 3. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event04'] = array(
      'title' => t('4. Event'),
      'help' => t('Anzahl Punkte des 4. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event05'] = array(
      'title' => t('5. Event'),
      'help' => t('Anzahl Punkte des 5. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event06'] = array(
      'title' => t('6. Event'),
      'help' => t('Anzahl Punkte des 6. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event07'] = array(
      'title' => t('7. Event'),
      'help' => t('Anzahl Punkte des 7. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event08'] = array(
      'title' => t('8. Event'),
      'help' => t('Anzahl Punkte des 8. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event09'] = array(
      'title' => t('9. Event'),
      'help' => t('Anzahl Punkte des 9. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event10'] = array(
      'title' => t('10. Event'),
      'help' => t('Anzahl Punkte des 10. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event11'] = array(
      'title' => t('11. Event'),
      'help' => t('Anzahl Punkte des 11. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event12'] = array(
      'title' => t('12. Event'),
      'help' => t('Anzahl Punkte des 12. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event13'] = array(
      'title' => t('13. Event'),
      'help' => t('Anzahl Punkte des 13. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event14'] = array(
      'title' => t('14. Event'),
      'help' => t('Anzahl Punkte des 14. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event15'] = array(
      'title' => t('15. Event'),
      'help' => t('Anzahl Punkte des 15. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event16'] = array(
      'title' => t('16. Event'),
      'help' => t('Anzahl Punkte des 16. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event17'] = array(
      'title' => t('17. Event'),
      'help' => t('Anzahl Punkte des 17. Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event_J'] = array(
      'title' => t('17. Event'),
      'help' => t('Anzahl Punkte des 1. Jugend-Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event_J'] = array(
      'title' => t('1. Jugend-Event'),
      'help' => t('Anzahl Punkte des 1. Jugend-Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event_V'] = array(
      'title' => t('1. Veteranen-Event'),
      'help' => t('Anzahl Punkte des 1. Veteranen-Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['event_F'] = array(
      'title' => t('1. Frauen-Event'),
      'help' => t('Anzahl Punkte des 1. Frauen-Ranglistenturniers.'),
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
  $data['npv_rl_einzel']['Jahr_01'] = array(
      'title' => t('Jahr_01'),
      'help' => t('Punkte 1 Jahr vorher.'),
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
  $data['npv_rl_einzel']['Jahr_02'] = array(
      'title' => t('Jahr_02'),
      'help' => t('Punkte 2 Jahre vorher.'),
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
  $data['npv_rl_einzel']['Starts'] = array(
      'title' => t('Starts'),
      'help' => t('Anzahl Starts.'),
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
  $data['npv_rl_einzel']['Pkte'] = array(
      'title' => t('Punkte'),
      'help' => t('Punkte.'),
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
  $data['npv_rl_einzel']['Rang'] = array(
      'title' => t('Rang'),
      'help' => t('Rang.'),
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
  $data['npv_rl_einzel']['Mittel'] = array(
      'title' => t('Mittel'),
      'help' => t('Punktedurchschnitt.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
          'float' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
  );
  $data['npv_rl_einzel']['Pkte_total'] = array(
      'title' => t('Pkte_total'),
      'help' => t('Gesamtpunktzahl, auch nicht in die Wertung eingeflossene.'),
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
  $data['npv_rl_einzel']['RgZuvor'] = array(
      'title' => t('RgZuvor'),
      'help' => t('Rang nach dem vorherigen Ranglistenturnier.'),
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
  $data['npv_rl_einzel']['Wert6'] = array(
      'title' => t('Wert6'),
      'help' => t('Kleinste Punktezahl der 6 Wertungen.'),
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
  $data['npv_rl_einzel']['JugPkt'] = array(
      'title' => t('JugPkt'),
      'help' => t('Punkte nur für die Jugendrangliste.'),
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
  $data['npv_rl_einzel']['JugRang'] = array(
      'title' => t('JugRang'),
      'help' => t('Rang innerhalb der Jugendrangliste.'),
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
  $data['npv_rl_einzel']['JugStarts'] = array(
      'title' => t('JugStarts'),
      'help' => t('Starts für die Jugendrangliste.'),
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
  $data['npv_rl_einzel']['VetPkt'] = array(
      'title' => t('VetPkt'),
      'help' => t('Punkte für die Veteranenrangliste.'),
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
  $data['npv_rl_einzel']['VetRang'] = array(
      'title' => t('VetRang'),
      'help' => t('Rang innerhalb der Veteranenrangliste.'),
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
  $data['npv_rl_einzel']['VetStarts'] = array(
      'title' => t('VetStarts'),
      'help' => t('Starts für die Veteranenrangliste.'),
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
  $data['npv_rl_einzel']['FemPkt'] = array(
      'title' => t('FemPkt'),
      'help' => t('Punkte für die Frauenrangliste.'),
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
  $data['npv_rl_einzel']['FemRg'] = array(
      'title' => t('FemRg'),
      'help' => t('Rang innerhalb der Frauenrangliste.'),
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
  $data['npv_rl_einzel']['FemStarts'] = array(
      'title' => t('FemStarts'),
      'help' => t('Starts für die Frauenrangliste.'),
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
  $data['npv_rl_einzel']['Jahr'] = array(
      'title' => t('Jahr'),
      'help' => t('Jahr dieser Rangliste.'),
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
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  
  //Eventtabelle
  $data['npv_rl_event']['table'] = array(
      'group' => 'NPV Ranglisten Events',
      'base' => array(
          'field' => array('InputSpalte'),
          'title' => 'NPV Ranglisten Events',
          'help' => 'Tabelle für NPV Ranglisten Events.',
      ),
  );
  $data['npv_rl_event']['InputSpalte'] = array(
      'title' => t('InputSpalte'),
      'help' => t('Interne Eventbezeichnung.'),
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
  $data['npv_rl_event']['EventDatum'] = array(
      'title' => t('EventDatum'),
      'help' => t('Datum des Events.'),
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
      'argument' => array(
          'handler' => 'views_handler_argument_date',
      ),
  );
  $data['npv_rl_event']['EventLast'] = array(
      'title' => t('EventLast'),
      'help' => t('Letzter Event Ja/Nein.'),
      'field' => array(
          'handler' => 'views_handler_field_boolean',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'ews_handler_filter_boolean_operator',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_event']['EventName'] = array(
      'title' => t('EventName'),
      'help' => t('Bezeichnung des Events.'),
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
  $data['npv_rl_event']['EventForm'] = array(
      'title' => t('EventForm'),
      'help' => t('Formation des Events (doublette,triplette,..).'),
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
  $data['npv_rl_event']['EventModus'] = array(
      'title' => t('EventModus'),
      'help' => t('Modus des Events (KO-ABCD,Schweizer,..).'),
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
  $data['npv_rl_event']['EventOrt'] = array(
      'title' => t('EventOrt'),
      'help' => t('Ort des Events.'),
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
  $data['npv_rl_event']['EventAusrichter'] = array(
      'title' => t('EventAusrichter'),
      'help' => t('Ausrichter des Events.'),
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
  $data['npv_rl_event']['NVPStarter'] = array(
      'title' => t('NVPStarter'),
      'help' => t('Anzahl Starter mit NPV-Lizenz.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
  );
  $data['npv_rl_event']['TotalStarter'] = array(
      'title' => t('TotalStarter'),
      'help' => t('Gesamt Anzahl Starter.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
  );
  $data['npv_rl_event']['NPVvereine'] = array(
      'title' => t('NPVvereine'),
      'help' => t('Anzahl NPV-Vereine.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
  );
  $data['npv_rl_event']['Jahr'] = array(
      'title' => t('Jahr'),
      'help' => t('Jahr dieser Rangliste.'),
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
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_event']['table']['join'] = array(
  // Index this array by the table name to which this table refers.
  // 'left_field' is the primary key in the referenced table.
  // 'field' is the foreign key in this table.
      'npv_rl_einzel' => array(
          'left_field' => 'Jahr',
          'field' => 'Jahr',
      ),
  );
  
  //Vereinstabelle
  $data['npv_rl_verein']['table'] = array(
      'group' => 'NPV Ranglisten Vereine',
      'base' => array(
          'field' => array('LizNr'),
          'title' => 'NPV Ranglisten Vereine',
          'help' => 'Tabelle für NPV Ranglisten Vereine.',
      ),
  );
  $data['npv_rl_verein']['LizNr'] = array(
      'title' => t('Lizenz-Nr.'),
      'help' => t('Lizenz-Nr. des Vereins.'),
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
  $data['npv_rl_verein']['Verein'] = array(
      'title' => t('Verein'),
      'help' => t('Name des Vereins.'),
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
  $data['npv_rl_verein']['zuvor'] = array(
      'title' => t('Zuvor'),
      'help' => t('Rang vor dem aktuellen.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['Rang'] = array(
      'title' => t('Rang'),
      'help' => t('Aktueller Rang.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['Punkte'] = array(
      'title' => t('Punkte'),
      'help' => t('Punkte des Vereins.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['Werte'] = array(
      'title' => t('Werte'),
      'help' => t('Anzahl berücksichtigter Wertungen.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['Aktive'] = array(
      'title' => t('Aktive'),
      'help' => t('Anzahl aktive Spieler des Vereins.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['Mittel'] = array(
      'title' => t('Mittel'),
      'help' => t('Punktedurchschnitt.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
          'float' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['Total'] = array(
      'title' => t('Total'),
      'help' => t('Alle Punkte des Vereins, auch die nicht gewerteten.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['Starts'] = array(
      'title' => t('Starts'),
      'help' => t('Anzahl Starts.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['zuletzt'] = array(
      'title' => t('zuletzt'),
      'help' => t('Anzahl Punkte beim letzten Wettbewerb.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['RgJahr_1'] = array(
      'title' => t('RgJahr-1'),
      'help' => t('Rang im Jahr vorher.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['RgJahr_2'] = array(
      'title' => t('RgJahr-2'),
      'help' => t('Rang im Jahr vorher.'),
      'field' => array(
          'handler' => 'views_handler_field_numeric',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['Jahr'] = array(
      'title' => t('Jahr'),
      'help' => t('Jahr dieser Vereinswertung.'),
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
          'handler' => 'views_handler_argument_numeric',
      ),
  );
  $data['npv_rl_verein']['table']['join'] = array(
  // Index this array by the table name to which this table refers.
  // 'left_field' is the primary key in the referenced table.
  // 'field' is the foreign key in this table.
      'npv_rl_einzel' => array(
          'left_field' => 'join_einzel',
          'field' => 'join_einzel',
      ),
  );
  return $data;
}
