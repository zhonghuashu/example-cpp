## ASN.1 syntax file
- Checks asn1 syntax file
```shell
# Use code asn1parser tool to generate c
apt install libtasn1-bin

cd build_x86_64
asn1Parser -c sensor_data.asn
asn1Parser -c my_schema.asn
```