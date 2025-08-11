#ifndef WEBPAGE_H
#define WEBPAGE_H
const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8"/>
  <title>Temperature API Info</title>
  <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
  <style>
    .card { background: #fff; padding: 2em; border-radius: 1em; width: 90vw; max-width: 500px; box-shadow: 0 4px 16px rgba(0,0,0,0.15); text-align: center; }
    p, code, pre { font-size: 0.9em; word-break: break-word; }
    body { font-family: Arial, sans-serif; background: #f0f0f0; color: #333; margin: 0; min-height: 100vh; display: flex; justify-content: center; align-items: center; }
    h1 { font-size: 2.2em; }
    code { background: #eef4f8; padding: 0.5em 0.5em; border-radius: 0.5em; font-family: Consolas, monospace; }
    pre { background: #f7f9fa; padding: 1.3em; border-radius: 1em; color: #005500; text-align: left; overflow-x: auto; }
  </style>
</head>
<body>
  <div class="card">
    <h1>Temperature API Info</h1>
    <p>You can <strong>GET</strong> temperature using route:</p>
    <p><code>http://%ip_address%:80/data</code></p>
    <p>Content type is : <b>application/json</b></p>
    <p>Format is :</p>
    <pre>{"temperature": %TEMP%, "humidity": %HUMIDITY%}</pre>
  </div>
</body>
</html>
)rawliteral";
#endif

#ifndef FILE_NOT_FOUND_H
#define FILE_NOT_FOUND_H
const char FILE_NOT_FOUND[] PROGMEM = R"(
File Not Found

URI: %URI%
Method: %METHOD%
Arguments: %ARGS%

)";
#endif