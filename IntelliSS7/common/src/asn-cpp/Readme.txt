This directory contains source files of the ASN.1 C++ Runtime.


Important information:
----------------------

1) The Runtime ASN.1 classes suppose that the C++ operator new never fails to
   allocate memory. Therefore the functions set_new_handler and 
   standard_new_handler MUST be used to provide an error-handling mechanism 
   (see C++ standard).

2) Only the subset of ASN.1 that is relevant for telecoms ASN.1-based protocol
   is done (i.e. GSM MAP, INAP, CAMEL, ANSI 41...).

3) C++ namespaces are used to deal with multiple versions of the same protocol.

