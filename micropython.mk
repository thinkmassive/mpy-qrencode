QRENCODE_MOD_DIR := $(USERMOD_DIR)

# Add all C files to SRC_USERMOD.
SRC_USERMOD += $(QRENCODE_MOD_DIR)/qrcode/qrcode.c
SRC_USERMOD += $(QRENCODE_MOD_DIR)/qrencode.c

# We can add our module folder to include paths if needed
CFLAGS_USERMOD += -I$(QRENCODE_MOD_DIR)/qrcode