all: bonsai

bonsai:
	@clang main.c -o bonsai -lcurses -s -O2 -fno-ident -Wl,-z,norelro 
	@strip -S --strip-unneeded --remove-section=.note.gnu.gold-version --remove-section=.comment --remove-section=.note --remove-section=.note.gnu.build-id --remove-section=.note.ABI-tag bonsai
