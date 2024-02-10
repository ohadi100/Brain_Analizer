/**
 * @file
 * @brief     This file contains macros for automatically generating nanopb wrapper structs
 */
#ifndef NANO_PB_MACROS_HPP
#define NANO_PB_MACROS_HPP

/**
 * @brief Macro for generating an alias for nanopb entries used as rows in tables
 * @param   name entry name prefix (the message suffix is always Entry)
 */
#define USING_NPB_PERIODIC_REPORT_ENTRY(name) using name ## EntryNPB = com_vwg_connect_ids_idsperiodicreport_v1_ ## name ## Entry;

/**
 * @brief Macro for generating an alias for nanopb tables
 * @param   name table name prefix (the message suffix is always Table)
 */
#define USING_NPB_PERIODIC_REPORT_TABLE(name) using name ## TableNPB = com_vwg_connect_ids_idsperiodicreport_v1_ ## name ## Table;

/**
 * @brief Macro for generating aliases for both the entry and its associated table
 * @param   name name prefix
 */
#define USING_NPB_PERIODIC_REPORT(name)\
    USING_NPB_PERIODIC_REPORT_ENTRY(name)\
    USING_NPB_PERIODIC_REPORT_TABLE(name)

/**
 * @brief Helper macro used to declare a wrapper in order to serialize a table into its nanopb message
 * @param   name table name prefix (the table suffix is always Table)
 * @param   entrySuffix nanopb entry suffix (can be either NPB or empty)
 */
#define DECLARE_NPB_TABLE_HELPER(name, entrySuffix) class name ## Table: public name ## TableNPB\
{\
    public:\
    name ## Table();\
    ~name ## Table() = default; \
    name ## Table(const name ## Table&) = delete;\
    name ## Table( name ## Table&& rhs) noexcept;\
    name ## Table& operator=(name ## Table const&) = delete;\
    name ## Table& operator=(name ## Table&&) = delete;\
    void PrepareForSerialization();\
    std::vector< name ## Entry ## entrySuffix > Entries;\
};

/**
 * @brief Macro used to declare a wrapper in order to serialize a table into its nanopb message
 * Aliases for the entry and the associated table are also defined.
 * @param   name table name prefix (the table suffix is always Table)
 * @param   entrySuffix nanopb entry suffix (can be either NPB or empty)
 */
#define DECLARE_NPB_TABLE(name) USING_NPB_PERIODIC_REPORT(name)\
    DECLARE_NPB_TABLE_HELPER(name, NPB)

/**
 * @brief Macro used to begin the wrapper declaration to serialize an entry into its nanopb message.
 * Must be used together with END_DECLARE_NPB_ENTRY_TABLE.
 * Aliases for the entry and the associated table are also defined.
 * @param   name entry name prefix (the message suffix is always Entry)
 */
#define BEGIN_DECLARE_NPB_ENTRY_TABLE(name) USING_NPB_PERIODIC_REPORT(name)\
class name ## Entry : public name ## EntryNPB\
{\
    public:\
    name ## Entry();\
    ~name ## Entry() = default; \
    name ## Entry(const name ## Entry&) = delete;\
    name ## Entry( name ## Entry&& rhs) noexcept;\
    name ## Entry& operator=(name ## Entry const&) = delete; \
    name ## Entry& operator=( name ## Entry&&) = delete; \
    void PrepareForSerialization();

/**
 * @brief Macro used to end the wrapper declaration to serialize an entry into its nanopb message
 * and to declare the wrapper to serialize the associated table
 * Must be together with BEGIN_DECLARE_NPB_ENTRY_TABLE
 * @param   name table name prefix (the table suffix is always Table)
 */
#define END_DECLARE_NPB_ENTRY_TABLE(name) };\
    DECLARE_NPB_TABLE_HELPER(name,)

/**
 * @brief Macro used to declare inside a class a data member of type Table
 * @param   name table name prefix (the table suffix is always Table)
 */
#define DECLARE_DM_TABLE(name) name ## Table name;

/**
 * @brief Macro used to init a data member of type Table
 * @param   name table name prefix (the table suffix is always Table)
 * @param   field nanopb field name prefix (the field name suffix is always Table)
 */
#define INIT_DM_TABLE(name, field) has_ ## field ## Table = false;\
    field ## Table = name;

/**
 * @brief Macro used to move into a data member
 * @param   name data member name
 */
#define MOVE_DM(name) name(std::move(rhs.name))

/**
 * @brief Macro used to copy into a data member of type Table
 * @param   name data member name
 * @param   field nanopb field name prefix (the field name suffix is always Table)
 */
#define COPY_DM_TABLE(name, field) field ## Table = name;

/**
 * @brief Macro used to call PrepareForSerialization() on a data member of type Table,
 * then assign this data member to the corresponding nanopb field
 * @param   name data member name
 * @param   field nanopb field name prefix (the field name suffix is always Table)
 */
#define PREPARE_DM_TABLE(name, field) has_ ## field ## Table = !name.Entries.empty(); name.PrepareForSerialization();\
    field ## Table = name;

/**
 * @brief Macro used to define a wrapper in order to serialize a table into its nanopb message
 * The table entry is generated automatically by nanopb generator.
 * @param   name table name prefix (the table suffix is always Table)
 * @param   field nanopb field name prefix (the field name suffix is always Entries)
 */
#define DEFINE_NPB_TABLE(name, field) name ## Table::name ## Table():\
name ## TableNPB\
{\
    common::nanopb::CreateDecodingCallback< name ## EntryNPB, com_vwg_connect_ids_idsperiodicreport_v1_ ## name ## Entry_fields>(Entries)\
}\
{}\
\
name ## Table::name ## Table(name ## Table&& rhs) noexcept :\
name ## TableNPB{rhs},\
Entries(std::move(rhs.Entries))\
{\
    field ## Entries.arg = &Entries;\
}\
\
void name ## Table::PrepareForSerialization()\
{\
    field ## Entries = common::nanopb::CreateEncodingCallback< name ## EntryNPB, com_vwg_connect_ids_idsperiodicreport_v1_ ## name ## Entry_fields>(Entries);\
}

/**
 * @brief Macro used to define a wrapper in order to serialize a table into its nanopb message
 * The table entry is derived from the entry automatically generated by nanopb generator.
 * @param   name table name prefix (the table suffix is always Table)
 * @param   field nanopb field name prefix (the field name suffix is always Entries)
 */
#define DEFINE_NPB_ENTRY_TABLE(name, field) name ## Table::name ## Table():\
name ## TableNPB\
{\
    common::nanopb::CreateDecodingCallback< name ## EntryNPB, com_vwg_connect_ids_idsperiodicreport_v1_ ## name ## Entry_fields>(Entries)\
}\
{}\
\
name ## Table::name ## Table(name ## Table&& rhs) noexcept :\
name ## TableNPB{rhs},\
Entries(std::move(rhs.Entries))\
{\
    field ## Entries.arg = &Entries;\
}\
\
void name ## Table::PrepareForSerialization()\
{\
    for (auto& entry: Entries)\
    {\
        entry.PrepareForSerialization();\
    }\
    field ## Entries = common::nanopb::CreateEncodingCallback< name ## EntryNPB, com_vwg_connect_ids_idsperiodicreport_v1_ ## name ## Entry_fields>(Entries);\
}

/**
 * @brief Macro used to set an optional field generated by nanopb generator.
 * @param   entry entry with optional field
 * @param   field field name
 * @param   value field value
 */
#define SET_NPB_OPTIONAL_FIELD(entry, field, value) entry.field = value, entry.has_ ## field = true

/**
 * @brief Macro used to set a field generated by nanopb generator.
 * @param   entry entry
 * @param   field field name
 * @param   value field value
 */
#define SET_NPB_FIELD(entry, field, value) entry.field = value

/**
 * @brief Macro used to initialize an optional field generated by nanopb generator.
 * @param   entry entry with optional field
 * @param   field field name
 * @param   value optional value. The value type must be cm::optional<>
 */
#define INIT_NPB_OPTIONAL_FIELD(entry, field, optionalValue) (optionalValue) ? SET_NPB_OPTIONAL_FIELD(entry, field, *(optionalValue)) : entry.has_ ## field = false

/**
 * @brief Macro used to initialize a field generated by nanopb generator.
 * @param   entry entry
 * @param   field field name
 * @param   value optional value. The value type must be cm::optional<>
 */
#define INIT_NPB_FIELD(entry, field, optionalValue) \
    do { \
       if (optionalValue) { \
           entry.field = *(optionalValue); \
       } \
    } while (0)

#endif // NANO_PB_MACROS_HPP