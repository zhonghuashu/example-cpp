## ASN.1 syntax file
- Checks asn1 syntax file
```shell
# 使用 代码asn1Parser 工具生成 C
apt install libtasn1-bin

cd build_x86_64
asn1Parser -c sensor_data.asn
asn1Parser -c my_schema.asn
```