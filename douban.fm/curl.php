<?php
$ch = curl_init();
$options = array(
   CURLOPT_URL => "http://douban.fm/j/app/channels",
  CURLOPT_CUSTOMREQUEST => "GET"
);
curl_setopt_array($ch,$options);
$responce = json_decode(curl_exec($ch),true);
print_r($response);
?>
