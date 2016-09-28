========================================================================
    STATIC LIBRARY : Crypto Project Overview
========================================================================

Crypto_AES is a concrete class that derives from Crypto, use it for all your encryption needs
HexHelper a static class with methods used to convert binary 1 byte chars to their 2 byte hex equivelant 'D' => "44" and back
   this means that your binary strings double in size when converted to hex and vice versa. Not the most effecient way Base64 
   is better as the final size of the converted binary string is not doubled.  But this is fine for this project

Crypto is an Abstract Base Class (ABC) so you cannot instantiate it

Reindall a class that implements AES symetric encryption


