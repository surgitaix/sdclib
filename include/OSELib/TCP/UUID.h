#ifndef UUID_H
#define UUID_H
#include <iostream>
#include <vector>
#include <array>
#include <openssl/sha.h>
#include <uuid/uuid.h>


namespace Network {
    class UUID
    {
        enum class UUID_Variant {
            VarUnknown = -1,
            NCS = 0,
            DCE = 2,
            Microsoft = 6,
            Reserved = 7
        };

        enum class UUID_Version {
            Time,
            POSIX,
            MD5,
            Random,
            SHA1
        };

    public:
        /**
         * @brief UUID
         * Creates the NIL UUID
         */
        UUID();

        /**
         * @brief UUID
         * Copy constructor
         * @param uuid
         */
        UUID(const UUID& uuid);

        /**
         * @brief UUID
         * Creates a UUID based on the string representation given
         * @param stringRepresentation String representation of the UUID as hex code eg:123e4567-e89b-12d3-a456-426655440000
         * or urn:uuid:123e4567-e89b-12d3-a456-426655440000 or {123e4567-e89b-12d3-a456-426655440000}
         */
        UUID(const std::string& uuidStringRepresentation);

        ~UUID() = default;

        UUID& operator = (const UUID& uuid);

        /**
         * @brief isNil
         * Checks if the UUID is 00000000-0000-0000-0000-000000000000
         * @return
         */
        bool isNil();

        /**
         * @brief UUID
         * Creates a UUID based on the string representation given
         * @param stringRepresentation String representation of the UUID as hex code eg:123e4567-e89b-12d3-a456-426655440000
         * or urn:uuid:123e4567-e89b-12d3-a456-426655440000 or {123e4567-e89b-12d3-a456-426655440000}
         * @return true if the UUID was successfully set based on the string representation
         */
        bool setFromString(const std::string & uuidStringRepresentation);

        /**
         * @brief toString
         * @return string representation of the current UUID in the format 123e4567-e89b-12d3-a456-426655440000
         */
        const std::string toString() const;

        const std::vector<uint8_t> toBytes();

        UUID_Version version() const;

        UUID_Variant variant() const;

        //static UUID createUUID();

        /**
         * @brief createUUIDv5
         * @param UUIDNamespace
         * Namespace of the UUID
         * @param name
         * name for the calculation of the UUIDv5
         * @return UUID UUIDv5 based on the namespace and name given
         */
        static UUID createUUIDv5( UUID& UUIDNamespace, const std::string& name);

        bool static validUUIDString(const std::string & uuidStringRepresentation);

        //UUID comperatoren
        bool operator == (const UUID& uuid) const;
        bool operator != (const UUID& uuid) const;
        //needed to use UUID inside std::map
        bool operator <  (const UUID& uuid) const;
//        bool operator <= (const UUID& uuid) const;
//        bool operator >  (const UUID& uuid) const;
//        bool operator >= (const UUID& uuid) const;

    private:
        uint32_t _timeLow;
        uint16_t _timeMid;
        uint16_t _timeHiAndVersion;
        uint16_t _clockSeqHighReservedAndLow;
        std::array<uint8_t, 6> _node;
    };
} //

#endif // UUID_H
