--------------------------------------------------------------------------------

Test6 (based on GSM MAP).

--------------------------------------------------------------------------------

o Related only to InsertSubscriberData operation (one of the most complex
  operation).

o Test processing:

    - Create InsertSubscriberDataArg object.
    - Set various information in InsertSubscriberDataArg object.
    - Print InsertSubscriberDataArg (rely on ASN.1 C++ runtime pretty print).
    - Encode to ASN.1 according to BER.
    - Print encoded value (array of bytes).
    - Decode to ASN.1 according to BER (create InsertSubscriberDataArgDec 
      object).
    - Print InsertSubscriberDataArgDec.
    - Access various information in InsertSubscriberDataArgDec object and
      print results.

o It is possible to set information in an ASN.1 C++ object at different places
  (e.g. it is possible to set information in InsertSubscriberDataArg in 
  different functions that take InsertSubscriberDataArg as a parameter pointer
  to or reference to).

o An ASN.1 Encode error denote a wrong use of an ASN.1 type (e.g. like 
  forgetting to add a mandatory element to a SEQUENCE or using a too big or
  too small OCTET STRING value if clause SIZE is used in the ASN.1 
  specification).
