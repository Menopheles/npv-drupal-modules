<?php
// $Id$
/**
 * @file
 * Functions for autocomplete fields
 */

/**
 * Menu callback; Retrieve a JSON object containing autocomplete suggestions for existing users.
 */
function username_autocomplete($string = '') {
  $matches = array();
  if ($string) {
    $result = db_select('users', 'u')
    ->fields('u', array('name'))
    ->condition('name', '%' . $string . '%', 'like')
    ->orderBy('name', 'DESC')
    ->range(0, 10)
    ->execute();
    foreach ($result as $user) {
      $account = user_load_by_name($user->name);
      if (array_search('Ligamelder', $account->roles) === FALSE) {
      } 
      else {
        $matches[$user->name] = check_plain($user->name);
      }
    }
  }
  drupal_json_output($matches);
}