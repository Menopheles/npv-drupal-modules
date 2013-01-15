<?php
/**
 * @file 
 * Funktionen für das Bearbeiten der Ligaspielberichtsbögen für das Modul NPG-Liga
 */

/**
 * Menüaufruf zur Anzeige des Formulars Ligaspiel
 * 
 * @param string $idspiel
 *        Id Nr. des zu bearbeitenden Spiels
 * @return array Eingabeformular
 */
function npv_liga_spiel_edit($idspiel) {
  return drupal_get_form('npv_liga_spiel_edit_form', $idspiel);
}

function npv_liga_spiel_edit_form($form, $form_state, $idspiel) {
  $form = array();
  //Spieler
  $form['spieler'] = array(
      '#type' => 'fieldset',
      '#title' => t('Spieler/innen'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
  );
  $form['spieler']['info'] = array(
      '#markup' => 'Frauen bitte zuerst eintragen, Ersatzspieler aus einem anderen Team: "Ersatzspieler" ankreuzen.</br><table><tr><th>Spieler</th><th>Lizenz</th><th>Name, Vorname</th><th>Ersatzspieler</th></tr>',
  );
  for ($i = 1; $i <= 10; $i++) {
    $form['spieler']['kz_' . chr(64 + $i)] = array(
        '#markup' => '<tr><td><strong>' . chr(64 + $i) . '</strong></td>',
    );
    $form['spieler']['lizenz_' . chr(64 + $i)] = array(
      '#size' => '3',
      //'#weight' => '0',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 3,
      '#required' => TRUE,
        '#prefix' => '<td>',
        '#suffix' => '</td>',
    );
    $form['spieler']['name_' . chr(64 + $i)] = array(
      '#size' => '60',
      //'#weight' => '0',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 3,
      '#required' => TRUE,
        '#prefix' => '<td>',
        '#suffix' => '</td>',
    );
    $form['spieler']['e_' . chr(64 + $i)] = array(
      '#size' => '60',
      //'#weight' => '0',
      '#type' => 'checkbox',
      '#required' => TRUE,
        '#prefix' => '<td>',
        '#suffix' => '</td><tr>',
    );
  }
  $form['spieler']['info2'] = array(
      '#markup' => '</table>',
  );
  //Begegnung 1
  $form['begegnung_1'] = array(
      '#type' => 'fieldset',
      '#title' => t('1. Begegnung'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
  );
  $form['begegnung_1']['start'] = array(
      '#markup' => '<table>',
  );
  //1. Zeile
  $form['begegnung_1']['links'] = array(
      '#markup' => '<tr><td rowspan="13" class="deg-90">1. Begegnung</td>',
  );
  $form['begegnung_1']['begegnung'] = array(
      '#markup' => '<td colspan="2">Begegnung Nr.</td>',
  );
  $form['begegnung_1']['gegner'] = array(
      '#markup' => '<td colspan="6">Gegner</td></tr>',
  );
  //2. Zeile
  $form['begegnung_1']['begegnung_1'] = array(
      '#size' => '5',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 3,
      '#required' => TRUE,
      '#prefix' => '<tr><td colspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['gegner_1'] = array(
      '#size' => '60',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 30,
      '#required' => TRUE,
      '#prefix' => '<td colspan="6">',
      '#suffix' => '</td></tr>',
  );
  //3. Zeile
  $form['begegnung_1']['ueberschrift1_1'] = array(
      '#markup' => '<td colspan="2"></td>',
  );
  $form['begegnung_1']['ueberschrift2_1'] = array(
      '#markup' => '<td colspan="3">Spieler</td>',
  );
  $form['begegnung_1']['ueberschrift3_1'] = array(
      '#markup' => '<td colspan="2">Ergebnis</td>',
  );
  $form['begegnung_1']['ueberschrift4_1'] = array(
      '#markup' => '<td>Spiel</td></tr>',
  );
  //4. Zeile
  $form['begegnung_1']['triplette_1'] = array(
      '#markup' => '<tr><td rowspan="4" class="deg-90">Triplette</td>',
  );
  $form['begegnung_1']['triplette_mixte_1'] = array(
      '#markup' => '<td>mixte</td>',
  );
  $form['begegnung_1']['triplette_mixte_spieler_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_mixte_spieler_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_mixte_spieler_3_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_mixte_punkte_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_mixte_punkte_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_mixte_spiel_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //5. Zeile
  $form['begegnung_1']['triplette_mixte_w_1'] = array(
      '#markup' => '<tr><td>Wechsel</td>',
  );
  $form['begegnung_1']['triplette_mixte_spieler_1w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_mixte_spieler_2w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_mixte_spieler_3w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  // triplette 2
  //6. Zeile
  $form['begegnung_1']['triplette_2_1'] = array(
      '#markup' => '<tr><td>Nr. 2</td>',
  );
  $form['begegnung_1']['triplette_2_spieler_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_2_spieler_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_2_spieler_3_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_2_punkte_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_2_punkte_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_2_spiel_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //7. Zeile
  $form['begegnung_1']['triplette_2_w_1'] = array(
      '#markup' => '<tr><td>Wechsel</td>',
  );
  $form['begegnung_1']['triplette_2_spieler_1w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_2_spieler_2w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['triplette_2_spieler_3w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  //Doublette
  //8. Zeile
  $form['begegnung_1']['doublette_1'] = array(
      '#markup' => '<tr><td rowspan="6" class="deg-90">Doublette</td>',
  );
  $form['begegnung_1']['doublette_mixte_1'] = array(
      '#markup' => '<td colspan="2">mixte</td>',
  );
  $form['begegnung_1']['doublette_mixte_spieler_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_mixte_spieler_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_mixte_punkte_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_mixte_punkte_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_mixte_spiel_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //9. Zeile
  $form['begegnung_1']['doublette_mixte_w_1'] = array(
      '#markup' => '<tr><td colspan="2">Wechsel</td>',
  );
  $form['begegnung_1']['doublette_mixte_spieler_1w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_mixte_spieler_2w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  // doublette 2
  //10. Zeile
  $form['begegnung_1']['doublette_2_1'] = array(
      '#markup' => '<tr><td colspan="2">Nr. 2</td>',
  );
  $form['begegnung_1']['doublette_2_spieler_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_2_spieler_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_2_punkte_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_2_punkte_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_2_spiel_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //11. Zeile
  $form['begegnung_1']['doublette_2w_1'] = array(
      '#markup' => '<tr><td colspan="2">Wechsel</td>',
  );
  $form['begegnung_1']['doublette_2_spieler_1w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_2_spieler_2w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  // doublette 3
  //12. Zeile
  $form['begegnung_1']['doublette_3_1'] = array(
      '#markup' => '<tr><td colspan="2">Nr. 3</td>',
  );
  $form['begegnung_1']['doublette_3_spieler_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_3_spieler_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_3_punkte_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_3_punkte_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_3_spiel_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //13. Zeile
  $form['begegnung_1']['doublette_3w_1'] = array(
      '#markup' => '<tr><td colspan="2">Wechsel</td>',
  );
  $form['begegnung_1']['doublette_3_spieler_1w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['doublette_3_spieler_2w_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  //14. Zeile
  $form['begegnung_1']['gesamt_1'] = array(
      '#markup' => '<tr><td colspan="6"></td>',
  );
  $form['begegnung_1']['gesamt_punkte_1_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['gesamt_punkte_2_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_1']['gesamt_spiel_1'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  $form['begegnung_1']['ende_1'] = array(
      '#markup' => '</table>',
  );
  //Begegnung 2
  $form['begegnung_2'] = array(
      '#type' => 'fieldset',
      '#title' => t('2. Begegnung'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
  );
  $form['begegnung_2']['start_2'] = array(
      '#markup' => '<table>',
  );
  //1. Zeile
  $form['begegnung_2']['links_2'] = array(
      '#markup' => '<tr><td rowspan="13" class="deg-90">2. Begegnung</td>',
  );
  $form['begegnung_2']['begegnung_2'] = array(
      '#markup' => '<td colspan="2">Begegnung Nr.</td>',
  );
  $form['begegnung_2']['gegner'] = array(
      '#markup' => '<td colspan="6">Gegner</td></tr>',
  );
  //2. Zeile
  $form['begegnung_2']['begegnung_2'] = array(
      '#size' => '5',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 3,
      '#required' => TRUE,
      '#prefix' => '<tr><td colspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['gegner_2'] = array(
      '#size' => '60',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 30,
      '#required' => TRUE,
      '#prefix' => '<td colspan="6">',
      '#suffix' => '</td></tr>',
  );
  //3. Zeile
  $form['begegnung_2']['ueberschrift1_2'] = array(
      '#markup' => '<td colspan="2"></td>',
  );
  $form['begegnung_2']['ueberschrift2_2'] = array(
      '#markup' => '<td colspan="3">Spieler</td>',
  );
  $form['begegnung_2']['ueberschrift3_2'] = array(
      '#markup' => '<td colspan="2">Ergebnis</td>',
  );
  $form['begegnung_2']['ueberschrift4_2'] = array(
      '#markup' => '<td>Spiel</td></tr>',
  );
  //4. Zeile
  $form['begegnung_2']['triplette_2'] = array(
      '#markup' => '<tr><td rowspan="4" class="deg-90">Triplette</td>',
  );
  $form['begegnung_2']['triplette_mixte_2'] = array(
      '#markup' => '<td>mixte</td>',
  );
  $form['begegnung_2']['triplette_mixte_spieler_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_mixte_spieler_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_mixte_spieler_3_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_mixte_punkte_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_mixte_punkte_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_mixte_spiel_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //5. Zeile
  $form['begegnung_2']['triplette_mixte_w_2'] = array(
      '#markup' => '<tr><td>Wechsel</td>',
  );
  $form['begegnung_2']['triplette_mixte_spieler_1w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_mixte_spieler_2w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_mixte_spieler_3w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  // triplette 2
  //6. Zeile
  $form['begegnung_2']['triplette_2_2'] = array(
      '#markup' => '<tr><td>Nr. 2</td>',
  );
  $form['begegnung_2']['triplette_2_spieler_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_2_spieler_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_2_spieler_3_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_2_punkte_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_2_punkte_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_2_spiel_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //7. Zeile
  $form['begegnung_2']['triplette_2_w_2'] = array(
      '#markup' => '<tr><td>Wechsel</td>',
  );
  $form['begegnung_2']['triplette_2_spieler_1w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_2_spieler_2w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['triplette_2_spieler_3w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  //Doublette
  //8. Zeile
  $form['begegnung_2']['doublette_2'] = array(
      '#markup' => '<tr><td rowspan="6" class="deg-90">Doublette</td>',
  );
  $form['begegnung_2']['doublette_mixte_2'] = array(
      '#markup' => '<td colspan="2">mixte</td>',
  );
  $form['begegnung_2']['doublette_mixte_spieler_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_mixte_spieler_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_mixte_punkte_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_mixte_punkte_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_mixte_spiel_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //9. Zeile
  $form['begegnung_2']['doublette_mixte_w_2'] = array(
      '#markup' => '<tr><td colspan="2">Wechsel</td>',
  );
  $form['begegnung_2']['doublette_mixte_spieler_1w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_mixte_spieler_2w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  // doublette 2
  //10. Zeile
  $form['begegnung_2']['doublette_2_2'] = array(
      '#markup' => '<tr><td colspan="2">Nr. 2</td>',
  );
  $form['begegnung_2']['doublette_2_spieler_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_2_spieler_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_2_punkte_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_2_punkte_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_2_spiel_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //11. Zeile
  $form['begegnung_2']['doublette_2w_2'] = array(
      '#markup' => '<tr><td colspan="2">Wechsel</td>',
  );
  $form['begegnung_2']['doublette_2_spieler_1w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_2_spieler_2w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  // doublette 3
  //12. Zeile
  $form['begegnung_2']['doublette_3_2'] = array(
      '#markup' => '<tr><td colspan="2">Nr. 3</td>',
  );
  $form['begegnung_2']['doublette_3_spieler_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_3_spieler_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_3_punkte_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_3_punkte_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_3_spiel_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //13. Zeile
  $form['begegnung_2']['doublette_3w_2'] = array(
      '#markup' => '<tr><td colspan="2">Wechsel</td>',
  );
  $form['begegnung_2']['doublette_3_spieler_1w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['doublette_3_spieler_2w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  //14. Zeile
  $form['begegnung_2']['gesamt_2'] = array(
      '#markup' => '<tr><td colspan="6"></td>',
  );
  $form['begegnung_2']['gesamt_punkte_1_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['gesamt_punkte_2_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_2']['gesamt_spiel_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  $form['begegnung_2']['ende_2'] = array(
      '#markup' => '</table>',
  );
  //Begegnung 3
  $form['begegnung_3'] = array(
      '#type' => 'fieldset',
      '#title' => t('3. Begegnung'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
  );
  $form['begegnung_3']['start_3'] = array(
      '#markup' => '<table>',
  );
  //1. Zeile
  $form['begegnung_3']['links_3'] = array(
      '#markup' => '<tr><td rowspan="13" class="deg-90">3. Begegnung</td>',
  );
  $form['begegnung_3']['begegnung_u_3'] = array(
      '#markup' => '<td colspan="2">Begegnung Nr.</td>',
  );
  $form['begegnung_3']['gegner'] = array(
      '#markup' => '<td colspan="6">Gegner</td></tr>',
  );
  //2. Zeile
  $form['begegnung_3']['begegnung_3'] = array(
      '#size' => '5',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 3,
      '#required' => TRUE,
      '#prefix' => '<tr><td colspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['gegner_3'] = array(
      '#size' => '60',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 30,
      '#required' => TRUE,
      '#prefix' => '<td colspan="6">',
      '#suffix' => '</td></tr>',
  );
  //3. Zeile
  $form['begegnung_3']['ueberschrift1_3'] = array(
      '#markup' => '<td colspan="2"></td>',
  );
  $form['begegnung_3']['ueberschrift2_3'] = array(
      '#markup' => '<td colspan="3">Spieler</td>',
  );
  $form['begegnung_3']['ueberschrift3_3'] = array(
      '#markup' => '<td colspan="2">Ergebnis</td>',
  );
  $form['begegnung_3']['ueberschrift4_3'] = array(
      '#markup' => '<td>Spiel</td></tr>',
  );
  //4. Zeile
  $form['begegnung_3']['triplette_3'] = array(
      '#markup' => '<tr><td rowspan="4" class="deg-90">Triplette</td>',
  );
  $form['begegnung_3']['triplette_mixte_3'] = array(
      '#markup' => '<td>mixte</td>',
  );
  $form['begegnung_3']['triplette_mixte_spieler_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_mixte_spieler_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_mixte_spieler_3_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_mixte_punkte_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_mixte_punkte_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_mixte_spiel_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //5. Zeile
  $form['begegnung_3']['triplette_mixte_w_3'] = array(
      '#markup' => '<tr><td>Wechsel</td>',
  );
  $form['begegnung_3']['triplette_mixte_spieler_1w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_mixte_spieler_2w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_mixte_spieler_3w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  // triplette 2
  //6. Zeile
  $form['begegnung_3']['triplette_2_3'] = array(
      '#markup' => '<tr><td>Nr. 2</td>',
  );
  $form['begegnung_3']['triplette_2_spieler_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_2_spieler_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_2_spieler_3_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_2_punkte_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_2_punkte_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_2_spiel_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //7. Zeile
  $form['begegnung_3']['triplette_2_w_3'] = array(
      '#markup' => '<tr><td>Wechsel</td>',
  );
  $form['begegnung_3']['triplette_2_spieler_1w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_2_spieler_2w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['triplette_2_spieler_3w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  //Doublette
  //8. Zeile
  $form['begegnung_3']['doublette_3'] = array(
      '#markup' => '<tr><td rowspan="6" class="deg-90">Doublette</td>',
  );
  $form['begegnung_3']['doublette_mixte_3'] = array(
      '#markup' => '<td colspan="2">mixte</td>',
  );
  $form['begegnung_3']['doublette_mixte_spieler_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_mixte_spieler_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_mixte_punkte_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_mixte_punkte_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_mixte_spiel_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //9. Zeile
  $form['begegnung_3']['doublette_mixte_w_3'] = array(
      '#markup' => '<tr><td colspan="2">Wechsel</td>',
  );
  $form['begegnung_3']['doublette_mixte_spieler_1w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_mixte_spieler_2w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  // doublette 2
  //10. Zeile
  $form['begegnung_3']['doublette_2_3'] = array(
      '#markup' => '<tr><td colspan="2">Nr. 2</td>',
  );
  $form['begegnung_3']['doublette_2_spieler_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_2_spieler_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_2_punkte_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_2_punkte_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_2_spiel_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //11. Zeile
  $form['begegnung_3']['doublette_2w_3'] = array(
      '#markup' => '<tr><td colspan="2">Wechsel</td>',
  );
  $form['begegnung_3']['doublette_2_spieler_1w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_2_spieler_3w_2'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  // doublette 3
  //12. Zeile
  $form['begegnung_3']['doublette_3_3'] = array(
      '#markup' => '<tr><td colspan="2">Nr. 3</td>',
  );
  $form['begegnung_3']['doublette_3_spieler_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_3_spieler_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_3_punkte_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_3_punkte_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_3_spiel_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td rowspan="2">',
      '#suffix' => '</td></tr>',
  );
  //13. Zeile
  $form['begegnung_3']['doublette_3w_3'] = array(
      '#markup' => '<tr><td colspan="2">Wechsel</td>',
  );
  $form['begegnung_3']['doublette_3_spieler_1w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['doublette_3_spieler_2w_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  //14. Zeile
  $form['begegnung_3']['gesamt_3'] = array(
      '#markup' => '<tr><td colspan="6"></td>',
  );
  $form['begegnung_3']['gesamt_punkte_1_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['gesamt_punkte_2_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 2,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td>',
  );
  $form['begegnung_3']['gesamt_spiel_3'] = array(
      '#size' => '2',
      '#type' => 'textfield',
      '#default_value' => '',
      '#maxlength' => 1,
      '#required' => TRUE,
      '#prefix' => '<td>',
      '#suffix' => '</td></tr>',
  );
  $form['begegnung_3']['ende_3'] = array(
      '#markup' => '</table>',
  );
  return $form;
}