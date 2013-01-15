<?php
/**
 * @file
 * Views Integration für Modul NPV-Liga
 */

/**
 * Implements hook_views_data
 *
 * @return array Datenstruktur für views-integration
 */
function npv_liga_views_data() {
  /* Ligen */
  $data['npv_liga_liga']['table'] = array(
      'group' => 'NPV Liga',
      'base' => array(
          'field' => array('idliga'),
          'title' => 'NPV Liga Ligen',
          'help' => 'Tabelle für NPV Ligen.',
      ),
  );
  $data['npv_liga_liga']['idliga'] = array(
      'title' => t('Liga-ID'),
      'help' => t('Liga-ID.'),
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
  $data['npv_liga_liga']['name'] = array(
      'title' => t('Liga Bezeichnung'),
      'help' => t('Liga Bezeichnung.'),
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
  $data['npv_liga_liga']['jahr'] = array(
      'title' => t('Liga-Jahr'),
      'help' => t('Jahr in dem die Liga ausgetragen wird.'),
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
  $data['npv_liga_liga']['date_cre'] = array(
      'title' => t('Liga erstellt am'),
      'help' => t('Datum an dem diese Liga erstellt wurde.'),
      'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort_date',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_date',
      ),
  );
  $data['npv_liga_liga']['date_ame'] = array(
      'title' => t('Liga geändert am'),
      'help' => t('Datum an dem diese Liga zuletzt geändert wurde.'),
      'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort_date',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_date',
      ),
  );
  $data['npv_liga_liga']['aufsteiger'] = array(
      'title' => t('Aufsteiger'),
      'help' => t('Aufsteiger bis einschliesslich Platz.'),
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
  $data['npv_liga_liga']['absteiger'] = array(
      'title' => t('Absteiger'),
      'help' => t('Absteiger ab Platz.'),
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
  $data['npv_liga_liga']['freigabe'] = array(
      'title' => t('Freigabe'),
      'help' => t('Tabelle wurde vom Ligawart freigegeben.'),
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
  $data['npv_liga_liga']['table']['join'] = array(
  // Index this array by the table name to which this table refers.
  // 'left_field' is the primary key in the referenced table.
  // 'field' is the foreign key in this table.
      'npv_liga_ligateam' => array(
          'left_field' => 'idliga',
          'field' => 'idliga',
      ),
      'npv_liga_begegnung' => array(
          'left_field' => 'idliga',
          'field' => 'idliga',
      ),
      'npv_liga_ligatabelle' => array(
          'left_field' => 'idliga',
          'field' => 'idliga',
      ),
  );
  /* Ligateams */
  $data['npv_liga_ligateam']['table'] = array(
      'group' => 'NPV Liga Teams',
      'base' => array(
          'field' => array('idligateam'),
          'title' => 'NPV Liga Teams',
          'help' => 'Tabelle für Teams der NPV Ligen.',
      ),
  );
  $data['npv_liga_ligateam']['idligateam'] = array(
      'title' => t('Ligateam-ID'),
      'help' => t('Ligateam-ID.'),
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
  $data['npv_liga_ligateam']['name'] = array(
      'title' => t('Ligateam Bezeichnung'),
      'help' => t('Ligateam Bezeichnung.'),
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
  $data['npv_liga_ligateam']['idverein'] = array(
      'title' => t('Vereins-ID des Ligateams'),
      'help' => t('Vereins-ID des Ligateams.'),
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
  $data['npv_liga_ligateam']['idliga'] = array(
      'title' => t('Liga-ID des Ligateams'),
      'help' => t('Liga-ID des Ligateams.'),
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
  $data['npv_liga_ligateam']['date_cre'] = array(
      'title' => t('Ligateam erstellt am'),
      'help' => t('Datum an dem dieses Ligateam erstellt wurde.'),
      'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort_date',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_date',
      ),
  );
  $data['npv_liga_ligateam']['date_ame'] = array(
      'title' => t('Ligateam geändert am'),
      'help' => t('Datum an dem dieses Ligateam zuletzt geändert wurde.'),
      'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort_date',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_date',
      ),
  );
  $data['npv_liga_ligateam']['table']['join'] = array(
  // Index this array by the table name to which this table refers.
  // 'left_field' is the primary key in the referenced table.
  // 'field' is the foreign key in this table.
      'npv_liga_ligatabelle' => array(
          'left_field' => 'idligateam',
          'field' => 'idligateam',
      ),
  );
  /* Ligabegegnungen */
  $data['npv_liga_begegnung']['table'] = array(
      'group' => 'NPV Liga Begegnungen',
      'base' => array(
          'field' => array('idbegegnung'),
          'title' => 'NPV Liga Begegnungen',
          'help' => 'Tabelle für Begegnungen(Spiele) der NPV Ligen.',
      ),
  );
  $data['npv_liga_begegnung']['idbegegnung'] = array(
      'title' => t('Ligabegegnungs-ID'),
      'help' => t('Ligabegegnungs-ID.'),
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
  $data['npv_liga_begegnung']['ort'] = array(
      'title' => t('Ort der Begegnung'),
      'help' => t('Ort der Begegnung.'),
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
  $data['npv_liga_begegnung']['date_game'] = array(
      'title' => t('Datum der Begegnung'),
      'help' => t('Datum an dem diese Begegnung stattfindet.'),
      'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort_date',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_date',
      ),
  );
  $data['npv_liga_begegnung']['uhrzeit'] = array(
      'title' => t('Zeit der Begegnung'),
      'help' => t('Zeit der Begegnung.'),
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
  $data['npv_liga_begegnung']['bahn'] = array(
      'title' => t('Bahn(en) für die Begegnung'),
      'help' => t('Bahn(en) für die Begegnung.'),
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
  $data['npv_liga_begegnung']['siege_team1'] = array(
      'title' => t('Siege Team 1'),
      'help' => t('Siege Team 1.'),
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
  $data['npv_liga_begegnung']['siege_team2'] = array(
      'title' => t('Siege Team 2'),
      'help' => t('Siege Team 2.'),
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
  $data['npv_liga_begegnung']['kugeln_team1'] = array(
      'title' => t('Kugeln Team 1'),
      'help' => t('Kugeln Team 1.'),
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
  $data['npv_liga_begegnung']['kugeln_team2'] = array(
      'title' => t('Kugeln Team 2'),
      'help' => t('Kugeln Team 2.'),
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
  $data['npv_liga_begegnung']['matchpunkt_team1'] = array(
      'title' => t('Matchpunkt Team 1'),
      'help' => t('Matchpunkt Team 1.'),
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
  $data['npv_liga_begegnung']['matchpunkt_team2'] = array(
      'title' => t('Matchpunkt Team 2'),
      'help' => t('Matchpunkt Team 2.'),
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
  $data['npv_liga_begegnung']['idteam1'] = array(
      'title' => t('ID-Team 1'),
      'help' => t('ID-Team 1.'),
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
      'relationship' => array(
          'base' => 'npv_liga_ligateam',
          'base field' => 'idligateam',
          'handler' => 'views_handler_relationship',
          'label' => t('Team 1 Relation'),
      ),
  );
  $data['npv_liga_begegnung']['idteam2'] = array(
      'title' => t('ID-Team 2'),
      'help' => t('ID-Team 2.'),
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
      'relationship' => array(
          'base' => 'npv_liga_ligateam',
          'base field' => 'idligateam',
          'handler' => 'views_handler_relationship',
          'label' => t('Team 2 Relation'),
      ),
  );
  $data['npv_liga_begegnung']['idliga'] = array(
      'title' => t('ID-Liga'),
      'help' => t('ID-Liga.'),
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
  $data['npv_liga_begegnung']['date_cre'] = array(
      'title' => t('Begegnung erstellt am'),
      'help' => t('Datum an dem diese Begegnung erstellt wurde.'),
      'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort_date',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_date',
      ),
  );
  $data['npv_liga_begegnung']['date_ame'] = array(
      'title' => t('Begegnung geändert am'),
      'help' => t('Datum an dem diese Begegnung zuletzt geändert wurde.'),
      'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort_date',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_date',
      ),
  );
  
  /* Ligatabelle */
  $data['npv_liga_ligatabelle']['table'] = array(
      'group' => 'NPV Liga Tabelle',
      'base' => array(
          'field' => array('idligatabelle'),
          'title' => 'NPV Liga Tabellen',
          'help' => 'Tabelle für Tabellen der NPV Ligen.',
      ),
  );
  $data['npv_liga_ligatabelle']['idligatabelle'] = array(
      'title' => t('Ligatabellen-ID'),
      'help' => t('Ligatabellen-ID.'),
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
  $data['npv_liga_ligatabelle']['platz'] = array(
      'title' => t('Platz'),
      'help' => t('Tabellenplatz.'),
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
  $data['npv_liga_ligatabelle']['matchpunkte'] = array(
      'title' => t('Matchpunkte'),
      'help' => t('Matchpunkte.'),
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
  $data['npv_liga_ligatabelle']['siege'] = array(
      'title' => t('Siege'),
      'help' => t('Anzahl Siege.'),
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
  $data['npv_liga_ligatabelle']['kugeldifferenz'] = array(
      'title' => t('Kugeldifferenz'),
      'help' => t('Kugeldifferenz.'),
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
  $data['npv_liga_ligatabelle']['kugelgewonnen'] = array(
      'title' => t('Gewonnene Kugeln'),
      'help' => t('Gewonnene Kugeln.'),
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
  $data['npv_liga_ligatabelle']['idligateam'] = array(
      'title' => t('Team ID'),
      'help' => t('Team ID.'),
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
  $data['npv_liga_ligatabelle']['idliga'] = array(
      'title' => t('Liga ID'),
      'help' => t('Liga ID.'),
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
  $data['npv_liga_ligatabelle']['date_cre'] = array(
      'title' => t('Datum Erstellung'),
      'help' => t('Datum der Erstellung.'),
      'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort_date',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_date',
      ),
  );
  $data['npv_liga_ligatabelle']['date_ame'] = array(
      'title' => t('Datum Änderung'),
      'help' => t('Datum der letzten Änderung.'),
      'field' => array(
          'handler' => 'views_handler_field_date',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort_date',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_date',
      ),
  );
  $data['npv_liga_ligatabelle']['siege_selbst'] = array(
      'title' => t('Siege selbst'),
      'help' => t('Siege selbst.'),
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
  $data['npv_liga_ligatabelle']['siege_gegner'] = array(
      'title' => t('Siege Gegner'),
      'help' => t('Siege Gegner.'),
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
  $data['npv_liga_ligatabelle']['spiele_selbst'] = array(
      'title' => t('Spiele selbst'),
      'help' => t('Spiele selbst.'),
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
  $data['npv_liga_ligatabelle']['spiele_gegner'] = array(
      'title' => t('Spiele Gegner'),
      'help' => t('Spiele Gegner.'),
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
  $data['npv_liga_ligatabelle']['kugeln_selbst'] = array(
      'title' => t('Kugeln selbst'),
      'help' => t('Kugeln selbst.'),
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
  $data['npv_liga_ligatabelle']['kugeln_gegner'] = array(
      'title' => t('Kugeln Gegner'),
      'help' => t('Kugeln Gegner.'),
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
  return $data;
}