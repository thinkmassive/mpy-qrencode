#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "py/obj.h"
#include "py/runtime.h"
#include "py/builtin.h"
#include "qrcode/qrcode.h"

/****************************** get_public_key33 ******************************/

STATIC mp_obj_t qrencode_make(mp_obj_t arg){
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(arg, &bufinfo, MP_BUFFER_READ);

	int qrSize = 3;
	int sizes[] = { 14, 26, 42, 62, 84, 106, 122, 152, 180, 213, 251, 287, 331, 362, 412, 480, 504, 560, 624, 666, 711, 779, 857, 911, 997, 1059, 1125, 1190 };
	int len = strlen((char *)bufinfo.buf);
	for(int i=0; i<sizeof(sizes)/sizeof(int); i++){
		if(sizes[i] > len){
			qrSize = i+1;
			break;
		}
	}

	QRCode qrcode;
	uint8_t * qrcodeData = (uint8_t *)calloc(qrcode_getBufferSize(qrSize), sizeof(uint8_t));
	qrcode_initText(&qrcode, qrcodeData, qrSize, 1, (char *)bufinfo.buf);

	char * qr = (char *)calloc((qrcode.size+1)*(qrcode.size+1), sizeof(char));
	char * c = qr;

	for (uint8_t y = 0; y < qrcode.size; y++) {
		for (uint8_t x = 0; x < qrcode.size; x++) {
			if(qrcode_getModule(&qrcode, x, y)){
				c[0] = 1;
		  	}else{
				c[0] = 0;
		  	}
		  	c++;
		}
		if(y < qrcode.size-1){
			c[0] = '\n';
		}
		c++;
	}
	free(qrcodeData);

    vstr_t vstr;
    vstr_init_len(&vstr, (qrcode.size+1)*(qrcode.size+1)-1);
    memcpy((byte*)vstr.buf, qr, (qrcode.size+1)*(qrcode.size+1)-1);
    c = NULL;
    free(qr);
    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(qrencode_make_obj, qrencode_make);

/****************************** MODULE ******************************/

STATIC const mp_rom_map_elem_t qrencode_module_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_qrencode) },
    { MP_ROM_QSTR(MP_QSTR_make), MP_ROM_PTR(&qrencode_make_obj) },
};
STATIC MP_DEFINE_CONST_DICT(qrencode_module_globals, qrencode_module_globals_table);

// Define module object.
const mp_obj_module_t qrencode_user_cmodule = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&qrencode_module_globals,
};

// Register the module to make it available in Python
MP_REGISTER_MODULE(MP_QSTR_qrencode, qrencode_user_cmodule, MODULE_QRENCODE_ENABLED);
