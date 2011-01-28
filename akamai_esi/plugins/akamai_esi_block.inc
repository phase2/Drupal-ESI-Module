<?php

class akamai_esi_block extends esi_block {
  private function send_esi() {
    return (isset($_SERVER['Akamai-Origin-Hop']) || isset($_SERVER['Surrogate-Capability']) || isset($_GET['ESI_FORCE']));
  }

  public function replace_block($block) {
    if ($this->send_esi()) {
      // TODO: the root path shouldn't be determined by the module
      $esi_base_path = base_path() . 'esi/block/' . $block->module . ':' . $block->delta . '/';
      return('<esi:choose>
          <esi:when test="$(HTTP_COOKIE{$(HTTP_COOKIE{\'ESISESS\'})})">
            <esi:include src="' . $esi_base_path . '$(HTTP_COOKIE{$(HTTP_COOKIE{\'ESISESS\'})})" />
          </esi:when>
          <esi:otherwise>
            <esi:include src="' . $esi_base_path . '0" />
          </esi:otherwise>
        </esi:choose>');
    }
    else {
      return(theme('block', $block));
    }
  }

  public function get_block($bid, $page) {
    list($module, $delta) = preg_split('/:/', $bid);
    $block = module_invoke($module, 'block', 'view', $delta);
    return theme('block', (object) $block);
  }
}
