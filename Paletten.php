<?php
/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
$form[${Feldbezeichung}] = array (
  '#access' => ${TRUE|FALSE},     //Whether the element is accessible or not; when FALSE, the element is not rendered and the user submitted value is not taken into consideration.
  '#after_build' => array(),      //An array of function names which will be called after the form or element is built.
  '#attributes' => array(),       //Additional HTML attributes, such as 'class' can be set using this mechanism.
  '#default_value' => '${default}',      //The value of the form element that will be displayed or selected initially if the form has not been submitted yet.
  '#description' => '${description}',        //The description of the form element. Make sure to enclose inside the t() function so this property can be translated.
  '#disabled' => ${TRUE|FALSE},   //Disables (greys out) a form input element. Note that disabling a form field doesn't necessarily prevent someone from submitting a value through DOM manipulation. It just tells the browser not to accept input.

);



?>
