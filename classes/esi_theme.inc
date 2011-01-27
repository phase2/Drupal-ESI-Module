<?php

class esi_theme {
  public function send_esi() {
    return arg(0) != 'esi';
  }
}
