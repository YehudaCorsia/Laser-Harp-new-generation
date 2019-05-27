import socket
import winsound
import threading
import os
from playsound import playsound

# Globals
STARTING_PORT = 5000
NUMBER_OF_LASERS = 5

def get_hertz(note):
	if note == "0":
		hertz = 523
	elif note == "1":
		hertz = 587
	elif note == "2":
		hertz = 659
	elif note == "3":
		hertz = 698
	elif note == "4":
		hertz = 784
	elif note == "5":
		hertz = 880
	else:
		hertz = 987
	return hertz


def play_note(note, duration=200):
	winsound.Beep(get_hertz(note), duration)

def play_sound(number):
	path = os.path.join("notes", str(number) + ".wav")
	playsound(path)


def listening(port):
	server_socket = socket.socket()
	server_socket.bind(('0.0.0.0', port))
	server_socket.listen(1)

	(client_socket, client_address) = server_socket.accept()

	return client_socket

def laser_handling(laser_number):
	global STARTING_PORT

	socket_laser = listening(STARTING_PORT + laser_number)
	is_played = False

	while True:
		request = socket_laser.recv(1).decode('ascii')
		if request == "0":
			is_played = False
		elif request == "1" and not is_played:
			#play_note(laser_number)
			play_sound(laser_number)
			is_played = True


def main():
	global NUMBER_OF_LASERS
	for i in range(0, NUMBER_OF_LASERS):
		laser_thread = threading.Thread(target=laser_handling, args=(i,))
		laser_thread.start()

	while True:
		pass


if __name__ == "__main__":
	main()
