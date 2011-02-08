<?php

class akamai_esi_block extends esi_block {
  public function send_esi() {
    return _akamai_esi_send_esi() || parent::send_esi();
  }

  public function replace_block($callback, $block) {
    switch ($block->cache) {
      case BLOCK_CACHE_PER_ROLE:
        $callback .= '/' . '$(HTTP_COOKIE{$(HTTP_COOKIE{\'R' . session_name() . '\'})})';
        break;
      case BLOCK_CACHE_PER_USER:
        $callback .= '/' . '$(HTTP_COOKIE{$(HTTP_COOKIE{\'' . session_name() . '\'})})';
        break;
    }
    return '<esi:include src="' . $callback . '" />';
  }
}
