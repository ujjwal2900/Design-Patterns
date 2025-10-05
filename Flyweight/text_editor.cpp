#include <iostream>
#include <vector>
#include <unordered_map>

class Character
{
public:
    explicit Character(char c) : m_char(c) {
        std::cout << "Invoked character class" << std::endl;
    }
    char getChar() const { return m_char;}

private:
    const char m_char;
};

class CharacterFactory
{
public:
    Character *insert_char(const char c)
    {
        auto it = m_CharacterPool.find(c);

        if(it != m_CharacterPool.end())
        {
            return it->second;
        }
        else
        {
            //auto [newIt,_] = m_CharacterPool.emplace(c, new Character(c));
            m_CharacterPool[c] = new Character(c);
            return m_CharacterPool[c];
        }
    }

    ~CharacterFactory()
    {
        for(auto it:m_CharacterPool)
        {
            delete it.second;
        }
    }

private:
    std::unordered_map<char, Character *> m_CharacterPool;
};

class Document
{
public:
    explicit Document(CharacterFactory *factory) : m_charFactory(factory) {}

    void insert(char c)
    {
        m_chars.push_back(m_charFactory->insert_char(c));
    }

    void print() const
    {
        for(const auto &c : m_chars)
        {
            std::cout << c->getChar();
        }
    }

private:
    std::vector<Character *> m_chars;
    CharacterFactory *m_charFactory;
};



int main()
{
    
    CharacterFactory m_CharFactory;
    Document doc(&m_CharFactory);

    doc.insert('a');
    doc.insert('a');
    doc.insert('b');
    doc.insert('b');
    doc.insert('c');
    doc.insert('c');
    doc.insert('d');
    doc.insert('d');
    doc.insert('e');
    doc.insert('e');
    doc.insert('e');

    
    doc.print();

    return 0;
}