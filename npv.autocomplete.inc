<?php
// $Id$
/**
 * @file
 * Functions for autocomplete fields
 */

/**
 * Menu callback Funktion für autocomplete Feld Sportbund
 * liefert max 10 Sportbundeinträge
 *
 * @param type $string
 */
function sportbund_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $query = db_select('npv_vereine', 'a')
      ->fields('a', array('sportbund'))
      ->distinct()
      ->range(0, 10)
      ->where('LOWER(sportbund) LIKE LOWER(:sb)', array(':sb' => '%'.$string.'%',));
    $result = $query->execute();
    while ($user = $result->fetchObject()) {
      $matches[$user->sportbund] = check_plain($user->sportbund);
    }
  }
  drupal_json_output($matches);
}

/**
 * Menu callback Funktion für autocomplete Feld Verein
 * liefert max 10 Vereine
 *
 * @param type $string
 */
function verein_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $query = db_select('npv_vereine', 'a')
      ->fields('a', array('name'))
      ->range(0, 10)
      ->where('LOWER(name) LIKE LOWER(:name)', array(':name' => '%'.$string.'%',));
    $result = $query->execute();
    foreach ($result as $user) {
      $matches[$user->name] = check_plain($user->name);
    }
  }

  drupal_json_output($matches);
}