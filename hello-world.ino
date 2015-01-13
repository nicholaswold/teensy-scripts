// Constants

const int led = 13;
const int ds = 1000;

void setup() {
  delay(DS); // Give me a second to connect
  pinMode(LED, OUTPUT); // ENGAGE STATUS LIGHT
  //digitalWrite(led, HIGH);
  
  spotlight("Terminal"); // open a terminal
  typeln("echo 'Hello, world!'");
  cmd(KEY_Q);
}

void spotlight(String application) {
  // Activate spotlight (Mac) and open
  // an application.
  cmd(KEY_SPACE);
  typeln(application);
}

void mod(int mod, int key) {
  Keyboard.press(mod);
  Keyboard.press(key);
  Keyboard.releaseAll();
  delay(ds); // Stops us from pressing the keys too fast!
}

void cmd(int key) {
  // Use CMD + key
  mod(MODIFIERKEY_GUI, key);
}

void typeln(String cmd) {
  Keyboard.print(cmd);
  delay(ds);
  Keyboard.println("");
  delay(ds*2);
}

void loop() {
  // Blink a lot - we're done!
  digitalWrite(led, HIGH);
  delay(ds);
  digitalWrite(led, LOW);
  delay(ds);
}
