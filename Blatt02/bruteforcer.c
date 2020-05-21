#include "bruteforcer.h"

int main(int argc, char *argv[]) {
	// Argumente checken
	if (argc != 4) {
		fprintf(stderr, "usage: %s pwdmaxlen workers hashfile\n", argv[0]);
		exit(1);
	}
	
	char *filename = NULL;
	hashes *loaded_hashes = NULL;
	
	// Kommandozeilenargumente auslesen und globale und lokale Variablen füllen
	// TODO: Vervollständigen
	// pwd_maxlen = ...
	// max_workers = ...
	// filename = ...
	pwd_maxlen = atoi(argv[1]);
	max_workers = atoi(argv[2]);
	filename = argv[3];
	// worker = ...
	// worker array mit 0 initialisieren
	// TODO
	worker = calloc(max_workers, sizeof(pid_t));
	
	INFO("\nBRUTEFORCER GESTARTET\n");
	INFO("---------------------\n");
	INFO("Maximale Passwortlänge: %d\n", pwd_maxlen);
	INFO("Anzahl der Worker: %d\n", max_workers);
	INFO("Hashes lesen aus Datei: %s\n", filename);
	INFO("---------------------\n\n");
	
	// Hashes in ein hashes struct laden
	// TODO
	// loaded_hashes = ...
	loaded_hashes = load_hashes(filename);
	// Main loop -> Iteriert über alle Hashes
	for (int i = 0; i < loaded_hashes->len; i++) {
		char *hash = loaded_hashes->array[i];

		// Hash mit crack_hash versuchen zu knacken
		// TODO

		pwd *cracked_pwd = crack_hash(hash);
		// Erfolg? -> print password
		// Fehlgeschlagen? -> Einfach weiter in der Schleife
		// fprintf(stdout, "halllooo %d\n", cracked_pwd == NULL);

		if(cracked_pwd != NULL) {
			printf("%s\n", cracked_pwd->buf);
		}
		
	}
	
	// Aufräumen und beenden
	// TODO
	free(worker);
	free(loaded_hashes);
	printf("passwort nicht gefunden");
	return 0;
}

// Versucht den Hash zu cracken, indem systematisch Passwörter generiert werden
// und darauf getestet wird, ob deren Hash mit hash übereinstimmt
// Returns pwd or NULL if no password was found
pwd *crack_hash(char *hash) {
	// Mit new_password() ein leeres Passwort anlegen
	pwd *password = new_password(pwd_maxlen);
	
	// Mit test_string() überprüfen, ob das (zuerst leere) Passwort zum Hash passt
	// In einer Schleife next_password() aufrufen, und das nächste Passwort überprüfen
	// Schleifenabbruch, sobald next_password() 0 zurückgibt => es gibt kein weiteres Passwort,
	// d.h. alle Passwörter bis zur maximalen Länge wurden bereits generiert und überprüft
	// ODER
	// Schleifenabbruch, wenn das Passwort gefunden wurde
	// TODO
	test_string(password->buf, hash);
	// fprintf(stdout, "%d %s\n", 1111, password->buf);

	int i = 1;
	while(i != 0 && test_string(password->buf, hash) == 0) {
		i = next_password(password);
		// fprintf(stdout, "%d %s\n", i, password->buf);
	}
	// fprintf(stdout, "%s %d", password->buf, test_string(password->buf, hash));

	
	// Aufräumen
	// TODO
	pwd *password_result = password;
	// free_password(password);

	// Passwort nicht gefunden -> NULL zurückgeben
	// Passwort gefunden -> das Password zurückgeben
	// TODO
	// fprintf(stdout, "test %d\n",test_string(password->buf, hash));
	if(test_string(password->buf, hash) == 1) {
		return password;
	} else {
		return NULL;
	}
}

// Berechnet den Hash von string und gibt 1 zurück, wenn er mit hash übereinstimmt, sonst 0
int test_string(char *string, char *hash) {
	// TODO
	char *string_hash = sha256(string);
	int equals = 0;
	// if the hash of string equals hash then set equals = 1
	if(strcmp(hash, string_hash) == 0) {
		equals = 1;
		free(string_hash);
	}
	return equals;
}

/**
 * Diese Funktion soll alle worker Kindprozesse die in dem Array "worker"
 * gespeichert sind darauf überprüfen, ob diese noch laufen oder bereits
 * beendet sind. Wenn ein Prozess beendet wurde soll der Eintrag in dem Array
 * gelöscht werden (auf 0 setzen), so dass dieser wieder zur Verfügung steht.
 *
 * return value:
 *   Diese Funktion soll die Anzahl der momentan im Hintergrund laufenden
 *   Prozesse zurückgeben. Prozesse die beendet wurden zählen nicht dazu.
 */
int update_worker() {
	int n = 0;
	for (int i = 0; i < max_workers; i++) {
		// TODO
	}
	
	return n;
}
