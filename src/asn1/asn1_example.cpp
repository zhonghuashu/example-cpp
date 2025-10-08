/**
 * @file asn1_simple.cpp
 * @brief Minimal libtasn1 ASN.1 BER encode/decode example
 * @details This file demonstrates the basic usage of libtasn1 for ASN.1 BER encoding and decoding.
 * Build command: g++ asn1_simple.cpp -ltasn1 -o asn1_simple
 * @author Shu, Zhong Hua
 * @date 2025-10-08
 */

#include <iostream>
#include <cstring>
#include <libtasn1.h>



int main()
{
    asn1_node asn1DefType = nullptr;
    asn1_node asn1Data = nullptr;
    int result;
    std::string error(ASN1_MAX_ERROR_DESCRIPTION_SIZE, '\0');

    // 1. Parse ASN.1 definition.
    result = asn1_parser2tree("my_schema.asn", &asn1DefType, &error[0]);
    if (result != ASN1_SUCCESS)
    {
        std::cerr << "ASN.1 parse error: " << error.c_str() << std::endl;
        return 1;
    }
    std::cout << "Print ASN.1 structure:\n";
    asn1_print_structure(stdout, asn1DefType, "MySchema", ASN1_PRINT_ALL);

    // 2. Create ASN.1 data structure.
    result = asn1_create_element(asn1DefType, "MySchema.MySeq", &asn1Data);
    if (result != ASN1_SUCCESS)
    {
        std::cerr << "Create element error" << std::endl;
        asn1_delete_structure(&asn1DefType);
        return 1;
    }

    // 3. Set value field.
    result = asn1_write_value(asn1Data, "value", "123", 8);
    if (result != ASN1_SUCCESS)
    {
        std::cerr << "Write value error" << std::endl;
        asn1_delete_structure(&asn1Data);
        asn1_delete_structure(&asn1DefType);
        return 1;
    }

    // 4. Encode to BER.
    unsigned char buffer[128];
    int berLen = sizeof(buffer);
    result = asn1_der_coding(asn1Data, "", (char*)buffer, &berLen, &error[0]);
    if (result != ASN1_SUCCESS)
    {
        std::cerr << "BER encoding error: " << error.c_str() << std::endl;
        asn1_delete_structure(&asn1Data);
        asn1_delete_structure(&asn1DefType);
        return 1;
    }
    std::cout << "BER encoded out buffer / length: " << buffer << ", " << berLen << std::endl;

    // 5. Decode BER.
    asn1_node asn1Decoded = nullptr;
    result = asn1_create_element(asn1DefType, "MySchema.MySeq", &asn1Decoded);
    if (result != ASN1_SUCCESS)
    {
        std::cerr << "Create decode element error" << std::endl;
        asn1_delete_structure(&asn1Data);
        asn1_delete_structure(&asn1DefType);
        return 1;
    }
    result = asn1_der_decoding(&asn1Decoded, (char*)buffer, berLen, &error[0]);
    if (result != ASN1_SUCCESS)
    {
        std::cerr << "BER decoding error: " << error.c_str() << std::endl;
    }
    else
    {
        char value[32];
        int valueLen = sizeof(value);
        result = asn1_read_value(asn1Decoded, "value", value, &valueLen);
        if (result == ASN1_SUCCESS)
        {
            value[valueLen] = '\0';
            std::cout << "Decoded value: " << value << std::endl;
        }
        else
        {
            std::cerr << "Read value error" << std::endl;
        }
    }

    // 6. Cleanup.
    asn1_delete_structure(&asn1Decoded);
    asn1_delete_structure(&asn1Data);
    asn1_delete_structure(&asn1DefType);
    return 0;
}
