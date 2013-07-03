<?php

/**
 * @file
 * Responsive Menu Administration UI
 * Implements the configuration screen.
 */

module_load_include('inc', 'responsive_menu', 'responsive_menu_common');

/**
 * Settings form as implemented by hook_menu.
 */
function responsive_menu_admin_settings($form, &$form_state) {

  $form['responsive_menu'] = array(
    '#type'          => 'fieldset',
    '#title'         => t('Responsive Nav Options'),
  );

  $form['responsive_menu']['responsive_menu_menu_class'] = array(
    '#type' => 'textfield',
    '#title' => t('Menu wrapper class'),
    '#description' => t('NOTE: Make sure it is a DIV surrounding the menu UL. <b>Do not include the leading dot</b>'),
    '#default_value' => variable_get('responsive_menu_menu_class', 'menu-block-wrapper'),
    '#size' => 100,
    '#required' => TRUE,
  );

  $form['responsive_menu']['responsive_menu_close'] = array(
    '#type' => 'textfield',
    '#title' => t('Single character you want to represent the close menu button'),
    '#default_value' => variable_get('responsive_menu_close', 'X'),
    '#size' => 1,
    '#required' => TRUE,
  );

  $form['responsive_menu']['responsive_menu_close_size'] = array(
    '#type' => 'textfield',
    '#title' => t('Set font size of close button'),
    '#description' => t('Enter a value such as "100px" or "10em" (without the quotation marks).'),
    '#default_value' => variable_get('responsive_menu_close_size', '20px'),
    '#size' => 1,
    '#required' => TRUE,
  );

  $form['responsive_menu']['responsive_menu_background'] = array(
    '#type' => 'textfield',
    '#title' => t('Set Color of close button'),
    '#description' => t('Enter a value such as "#fff" or "#ffffff" (without the quotation marks)'),
    '#default_value' => variable_get('responsive_menu_background', '#333'),
    '#size' => 10,
    '#required' => FALSE,
  );

  // $form['responsive_menu']['responsive_menu_open'] = array(
  //   '#type' => 'textfield',
  //   '#title' => t('Text/markup you want when menu is closed'),
  //   '#description' => t('<p>NOTE: Styling in CSS provides 3 bars with these spans</p>'),
  //   '#default_value' => variable_get('responsive_menu_open', ''),
  //   '#size' => 50,
  //   '#required' => FALSE,
  // );

  $form['responsive_menu']['responsive_menu_position'] = array(
    '#type' => 'textfield',
    '#title' => t('Menu reveal position'),
    '#description' => t('Left right or center positions'),
    '#default_value' => variable_get('responsive_menu_position', 'right'),
    '#size' => 10,
    '#required' => TRUE,
  );

  $form['responsive_menu']['responsive_menu_position_distance'] = array(
    '#type' => 'textfield',
    '#title' => t('Tweak the position of the menu'),
    '#description' => t('Will indent the position of the menu. Enter a value such as "100px" or "10em" (without the quotation marks).'),
    '#default_value' => variable_get('responsive_menu_position_distance', '0'),
    '#size' => 10,
    '#required' => TRUE,
  );

  // $form['responsive_menu']['responsive_menu_background_hover'] = array(
  //   '#type' => 'textfield',
  //   '#title' => t('Override CSS colours for the reveal hover'),
  //   '#description' => t('Enter a value such as "#fff" or "#ffffff" (without the quotation marks)'),
  //   '#default_value' => variable_get('responsive_menu_background_hover', '#000'),
  //   '#size' => 10,
  //   '#required' => FALSE,
  // );

  $form['responsive_menu']['responsive_menu_min_screen_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Set the screen width you want meanmenu to kick in at'),
    '#description' => t('<b>NOTE: This got to be the most important setting! this plugin does not use media query, so set it here!</b>'),
    '#default_value' => variable_get('responsive_menu_min_screen_width', '580'),
    '#size' => 10,
    '#required' => TRUE,
  );

  $form['responsive_menu']['responsive_menu_nav_push'] = array(
    '#type' => 'textfield',
    '#title' => t('Set a height here in px, em or % if you want to budge your layout now the navigation is missing.'),
    '#default_value' => variable_get('responsive_menu_nav_push', '0'),
    '#size' => 10,
    '#required' => FALSE,
  );

  $form['responsive_menu']['responsive_menu_show_children'] = array(
    '#type' => 'select',
    '#title' => t('Show menu children (sub navigation)'),
    '#options' => array(
         "true" => t('Yes'),
         "false" => t('No'),
      ),
    '#default_value' => variable_get('responsive_menu_show_children', 'true'),
    '#required' => TRUE,
  );

  $form['responsive_menu']['responsive_menu_show_children_collapse'] = array(
    '#type' => 'select',
    '#title' => t('Allow expand/collapse children'),
    '#options' => array(
         "true" => t('Yes'),
         "false" => t('No'),
      ),
    '#default_value' => variable_get('responsive_menu_show_children_collapse', 'true'),
    '#required' => TRUE,
  );

  $form['responsive_menu']['responsive_menu_expand_sign'] = array(
    '#type' => 'textfield',
    '#title' => t('Expand UL'),
    '#description' => t('Single character you want to represent the expand for ULs'),
    '#default_value' => variable_get('responsive_menu_expand_sign', '+'),
    '#size' => 25,
    '#required' => TRUE,
  );

  $form['responsive_menu']['responsive_menu_contract_sign'] = array(
    '#type' => 'textfield',
    '#title' => t('Contract UL'),
    '#description' => t('Single character or word you want to represent the contract for ULs'),
    '#default_value' => variable_get('responsive_menu_contract_sign', '-'),
    '#size' => 25,
    '#required' => TRUE,
  );

  $form['responsive_menu']['responsive_menu_remove_att'] = array(
    '#type' => 'select',
    '#title' => t('Remove classes and IDs'),
    '#options' => array(
         "true" => t('Yes'),
         "false" => t('No'),
      ),
    '#default_value' => variable_get('responsive_menu_remove_att', 'false'),
    '#required' => TRUE,
  );

  // Custom validation to make sure the user is entering numbers.
  $form['#validate'][] = 'responsive_menu_settings_validate';

  return system_settings_form($form);
}

/**
 * Custom validation for the settings form.
 */
function responsive_menu_settings_validate($form, &$form_state) {
  $menu_class = $form_state['values']['responsive_menu_menu_class'];
  $close = $form_state['values']['responsive_menu_close'];
  $close_size = $form_state['values']['responsive_menu_close_size'];
  $position = $form_state['values']['responsive_menu_position'];
  $position_distance = $form_state['values']['responsive_menu_position_distance'];
  $background = $form_state['values']['responsive_menu_background'];
  //$background_hover = $form_state['values']['responsive_menu_background_hover'];
  $min_screen_width = $form_state['values']['responsive_menu_min_screen_width'];
  $nav_push = $form_state['values']['responsive_menu_nav_push'];
  $show_children = $form_state['values']['responsive_menu_show_children'];
  $show_children_collapse = $form_state['values']['responsive_menu_show_children_collapse'];
  $menu_expand = $form_state['values']['responsive_menu_expand_sign'];
  $menu_contract = $form_state['values']['responsive_menu_contract_sign'];
  $remove_att = $form_state['values']['responsive_menu_remove_att'];
  
  //Check to make sure it is a number and that is a maximum of 2 digits.
  if (is_numeric($close) || strlen($close) > 1) {
    form_set_error('responsive_menu_close', t('You must enter only one letter'));
  }
  // if (!is_numeric($close_size) || strlen($close_size) > 2) {
  //   form_set_error('responsive_menu_close_size', t('This would have to be a 1 or 2 digit number!'));
  // }
  if (($position !== "left") && ($position !== "center") && ($position !== "right")) {
    form_set_error('responsive_menu_position', t('Values allowed: left, center or right'));
  }
  // if (!is_numeric($position_distance) || strlen($position_distance) > 3) {
  //   form_set_error('responsive_menu_position_distance', t('This should be a number between 0 and 999'));
  // }
  if (!preg_match('/^#(?:(?:[a-f0-9]{3}){1,2})$/i', $background)) {
    form_set_error('responsive_menu_background', t('This has to be a valid hex value!'));
  }
  // if (!preg_match('/^#(?:(?:[a-f0-9]{3}){1,2})$/i', $background_hover)) {
  //   form_set_error('responsive_menu_background_hover', t('This has to be a valid hex value!'));
  // }
  if (!is_numeric($min_screen_width) || strlen($min_screen_width) > 4) {
    form_set_error('responsive_menu_min_screen_width', t('This should be a number between 0 and 9999'));
  }
  // if (!is_numeric($nav_push) || strlen($nav_push) > 3) {
  //   form_set_error('responsive_menu_nav_push', t('This should be a number between 0 and 999'));
  // }
  // if (($show_children !== true) && ($show_children !== false)) {
  //   form_set_error('responsive_menu_show_children', t('Values allowed: true or false'));
  // }
  // if (($show_children_collapse !== true) && ($show_children_collapse !== false)) {
  //   form_set_error('responsive_menu_show_children_collapse', t('Values allowed: true or false'));
  // }
  if (is_numeric($menu_expand) || strlen($menu_expand) > 255) {
    form_set_error('responsive_menu_expand_sign', t('Only a word/string or character here'));
  }
  if (is_numeric($menu_contract) || strlen($menu_contract) > 255) {
    form_set_error('responsive_menu_contract_sign', t('Only a word/string or character here'));
  }
  // if (($remove_att !== true) && ($remove_att !== false)) {
  //   form_set_error('responsive_menu_remove_att', t('Values allowed: true or false'));
  // }
}
