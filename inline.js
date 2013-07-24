(function ($) {
          Drupal.behaviors.responsive_menu = {
              attach: function (context, settings) {
                var menuclass = Drupal.settings.responsive_menu.menu_class;
                $('.' + menuclass).meanmenu({
                meanMenuClass:Drupal.settings.responsive_menu.menu_class,
                meanMenuClose:Drupal.settings.responsive_menu.close_sign,
                meanMenuCloseSize:Drupal.settings.responsive_menu.close_size,
                //meanMenuOpen:Drupal.settings.responsive_menu.menu_open,
                meanRevealPosition:Drupal.settings.responsive_menu.menu_position,
                meanRevealPositionDistance:Drupal.settings.responsive_menu.menu_position_distance,
                meanRevealColour:Drupal.settings.responsive_menu.menu_background,
                meanRevealHoverColour:Drupal.settings.responsive_menu.menu_background_hover,
                meanScreenWidth:Drupal.settings.responsive_menu.min_width,
                meanNavPush:Drupal.settings.responsive_menu.nav_push,
                meanShowChildren:Drupal.settings.responsive_menu.show_children,
                meanExpandableChildren:Drupal.settings.responsive_menu.show_children_collapse,
                meanExpand:Drupal.settings.responsive_menu.expand_sign,
                meanContract:Drupal.settings.responsive_menu.contract_sign,
                meanRemoveAttrs:Drupal.settings.responsive_menu.remove_att,
              });
             }
         };
        })(jQuery);
