#ifndef CLI_HPP
#define CLI_HPP

#include <ncurses.h>
#include <iostream>
#include <csignal>

#include "csv_logdb.hpp"
#include "graph.hpp"

/**
 * @brief An object representation of the command line interface.
 */
class CLI
{
    public:
        CLI(const LogDatabase& logDb);
        FieldMap getFieldsFromUser();

    private:
        std::vector<std::string_view>
        fuzzySearchFields(const std::string& userInput);
        
        void removeField(std::vector<std::string_view>& fields,
                         const std::string_view& fieldToRemove);
        void printFields(WINDOW* stdscr,
                         const std::string& userInput) const;

        void handleBackspace(std::string& userInput);
        bool exitOnEnter(std::string& userInput);
        void handleNewChar(std::string& userInput, char newChar);

        FieldMap fieldsToFieldMap(const std::vector<std::string_view>& fields);


        // All of the fields the user can pick from
        const std::vector<std::string> m_allFields;
        // Below are string_views which are just views on allFields
        // Fields the user has currently picked
        std::vector<std::string_view> m_pickedFields;
        // Fields the user has not chosen 
        std::vector<std::string_view> m_unpickedFields;
        // Fields that show up in the fuzzy search
        std::vector<std::string_view> m_matchedFields;

        // Temporary storage, needed in order to output a FieldMap 
        const FieldMap m_fieldMap;
};

#endif