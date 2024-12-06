/* -- yaml.cpp -- */

#include "yaml.hpp"
#include <iostream>
using namespace std;

namespace YAML {
	/* Node class constructor */
	Node::Node(const string& identifier, void* data): m_identifier(identifier) {
		if (data != NULL)
			m_data = data;
		else
			m_data = NULL;
	}
	/* Node manipulation */
	bool Node::append(Node* node) {
		if (this->m_children.find(getID()) == NULL)
			return false;
		m_children.insert(node->getID(), node);
		return true;
	}
	Node* Node::getChild(const string& identifier) {
		return m_children.find(identifier);
	}
	string Node::getID() const {
		return m_identifier;
	}
	void Node::setData(void *data) {
		this->m_data = data;
	}

	/* yaml class */
	yaml::yaml(const string& filePath) {
		try {
			load(filePath);
		}
		catch(exception& e) {
			cout << e.what() << endl;
		}
	}
	yaml::~yaml(){}

	/**
	* @brief Calculates the level of indentation for the current line in the YAML file.
 	* 
 	* This function determines the number of leading spaces or tabs in the given line,
	* which indicates the hierarchical level of the current node in the YAML structure.
	*
	* @param line The current line of the YAML file as a string.
 	* @return int The indentation level (number of leading tabs).
 	*/
	int yaml::getIndentLevel(const string& line) {
		int IndentLevel = 0; /* must be tabs nor space */
		char tab = '\t';
		
		for (size_t i = 0; i < line.length(); i++) {
			if (line[i] == tab)
				IndentLevel++;
			else 
				break;
		}
		return IndentLevel;
	}

	void yaml::load(const string& filePath) {
		string line;
		/* file parsing
		 * TO-DO:
		 * 1. Open file.
		 * 2. Read line by line.
		 * 3. Handle indentation.
		 * 4. Create node hierarchy.
		 * 5. Handle different YAML structures.
		 */
		ifstream file(filePath.c_str());
		if (!file.is_open()) {
			file.close();
			throw runtime_error("failed to open file: " + filePath);
		}
		while (getline(file, line)) {
			if (line.empty())
				continue ;
			cout << "line: " << line <<  " Level: " << yaml::getIndentLevel(line) << endl;
		}
		file.close();	
	}
}
