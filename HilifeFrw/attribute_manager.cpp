/****************************************************************
 *  YAG2002 (http://yag2002.sourceforge.net)
 *  Copyright (C) 2005-2007, A. Botorabi
 *
 *  This program is free software; you can redistribute it and/or 
 *  modify it under the terms of the GNU Lesser General Public 
 *  License version 2.1 as published by the Free Software Foundation.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public 
 *  License along with this program; if not, write to the Free 
 *  Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
 *  MA  02111-1307  USA
 * 
 ****************************************************************/

/*###############################################################
 # attribute manager primarily used for game entities
 #
 #   date of creation:  01/13/2005
 #
 #   author:            ali botorabi (boto) 
 #      e-mail:         botorabi@gmx.net
 #
 ################################################################*/

#include "stable_headers.h"
#include "attribute_manager.h"



using namespace std;
namespace hilife
{

log4cpp::Category* AttributeManager::logger ;
AttributeManager::~AttributeManager()
{
	removeAllAttributes();
}

void AttributeManager::addAttribute( const std::string &name, const std::string &type, const std::string &value)
{
	if (!type.compare("int"))
	{
		int a;
		a=0;
		addAttribute(name,a);
	}
	else
	if (!type.compare("float"))
	{
		float a;
		a=0;
		addAttribute(name,a);
	}
	else
	if (!type.compare("string"))
	{
		std::string a("");
		addAttribute(name,a);
	}
	else
	if (!type.compare("bool"))
	{
		bool a;
		a=false;
		addAttribute(name,a);			
	}
	else
	if (!type.compare("vect3d"))
	{
		//TODO
		LOGGER_WARN << "TODO: Attribute type [" << type << "]";
		
	}
	else
	{
		LOGGER_WARN << "Can't find any rule for : Attribute type [" << type << "]" ;
		return;
	}
	setAttributeValueByString(name,value);
}

void AttributeManager::getAttributesAsString( vector< pair< string, string > >& attributes )
{
    vector< EntityAttributeBase* >::iterator p_beg = _attributes.begin(), p_end = _attributes.end();
    for ( ; p_beg != p_end; p_beg++ )
    {
        EntityAttributeBase* p_attribute = *p_beg;
        stringstream strvalue;
        unsigned int type = p_attribute->getType();
        switch ( type ) 
        {
            case EntityAttributeType::FLOAT:
            {
                float value = dynamic_cast< EntityAttribute< float >* >( p_attribute )->getValue();
                strvalue << value;
            }
            break;

            case EntityAttributeType::BOOL:
            {
                bool value = dynamic_cast< EntityAttribute< bool >* >( p_attribute )->getValue();
                strvalue << ( value ? "true" : "false" );
            }
            break;

            case EntityAttributeType::INTEGER:
            {
                int value = dynamic_cast< EntityAttribute< int >* >( p_attribute )->getValue();
                strvalue << value;
            }
            break;

            case EntityAttributeType::VECTOR3:
            {
				Ogre::Vector3 value = dynamic_cast< EntityAttribute< Ogre::Vector3 >* >( p_attribute )->getValue();
                strvalue << value.x << " " << value.y << " " << value.z;
            }
            break;

            case EntityAttributeType::STRING:
            {
                std::string value = dynamic_cast< EntityAttribute< std::string >* >( p_attribute )->getValue();
                strvalue << value;
            }
            break;

            default:
                assert( NULL && "invalid attribute type!" );
        }
        attributes.push_back( make_pair( p_attribute->getName(), strvalue.str() ) );
    }
}

bool AttributeManager::setAttributeValue( const string &name, const string &type, const string &value )
{
    bool bRet = false;
    stringstream strBuffer( value );

    // the type information is case-insensitve
    string citype;    
    for ( size_t i = 0; i < type.size(); i++ ) citype += toupper( type[ i ] );

    if ( ( citype == "BOOLEAN" ) || ( citype == "BOOL" ) ) 
    {
        string bVal;
        strBuffer >> bVal;
        bool   bValue = ( bVal == "true" ) ? true : false;
        bRet = setAttributeValue( name, bValue );
    }
    else if ( citype == "INTEGER" ) 
    {
        int iValue;
        strBuffer >> iValue;
        bRet = setAttributeValue( name, iValue );
    }
    else if ( citype == "FLOAT" ) 
    {
        float fValue;
        strBuffer >> fValue;
        bRet = setAttributeValue( name, fValue );
    }
    else if ( citype == "VECTOR3" ) 
    {
        Ogre::Vector3 vecValue;
        strBuffer >> vecValue.x >> vecValue.y >> vecValue.z ;
        bRet = setAttributeValue( name, vecValue );
    }
    else if ( citype == "STRING" ) 
    {
        bRet = setAttributeValue( name, value );
    }

    return bRet;
}

bool AttributeManager::setAttributeValueByString( const string& name, const string& valuestring )
{        
    vector< EntityAttributeBase* >::iterator p_beg = _attributes.begin(), p_end = _attributes.end();
    for ( ; p_beg != p_end; p_beg++ )
    {
        if ( ( *p_beg )->getName() == name )
            break;
    }
    if ( p_beg == p_end )
	{
		LOGGER_WARN << "Inexistant attribute [" << name << "]";
        return false;
	}

    EntityAttributeBase* p_attribute = *p_beg;
    stringstream strvalue;
    strvalue << valuestring;
    unsigned int type = p_attribute->getType();
    switch ( type ) 
    {
        case EntityAttributeType::FLOAT:
        {
            float value;
            strvalue >> value;
            setAttributeValue( name, value );
        }
        break;

        case EntityAttributeType::BOOL:
        {
            bool value = ( valuestring == "true" ? true : false );
            setAttributeValue( name, value );
        }
        break;

        case EntityAttributeType::INTEGER:
        {
            int value;
            strvalue >> value;
            setAttributeValue( name, value );
        }
        break;

        case EntityAttributeType::VECTOR3:
        {
			Ogre::Vector3 vecValue;
			strvalue >> vecValue.x >> vecValue.y >> vecValue.z ;
			setAttributeValue( name, vecValue );
        }
        break;

        case EntityAttributeType::STRING:
        {
            setAttributeValue( name, valuestring );
        }
        break;

        default:
			LOGGER_WARN << "invalid attribute type!";
            assert( NULL && "invalid attribute type!" );
    }

    return true;
}

bool AttributeManager::setAttributeValue( const string& name, const EntityAttributeBase& attribute )
{
    unsigned int type = attribute.getType();
    switch ( type ) 
    {
        case EntityAttributeType::FLOAT:
        {
            float value = dynamic_cast< const EntityAttribute< float >& >( attribute ).getValue();
            return setAttributeValue( name, value );
        }
        break;

        case EntityAttributeType::BOOL:
        {
            bool value = dynamic_cast< const EntityAttribute< bool >& >( attribute ).getValue();
            return setAttributeValue( name, value );
        }
        break;

        case EntityAttributeType::INTEGER:
        {
            int value = dynamic_cast< const EntityAttribute< int >& >( attribute ).getValue();
            return setAttributeValue( name, value );
        }
        break;

        case EntityAttributeType::VECTOR3:
        {
			Ogre::Vector3 value = dynamic_cast< const EntityAttribute< Ogre::Vector3 >& >( attribute ).getValue();
            return setAttributeValue( name, value );
        }
        break;

        case EntityAttributeType::STRING:
        {
            std::string value = dynamic_cast< const EntityAttribute< std::string >& >( attribute ).getValue();
            return setAttributeValue( name, value );
        }
        break;

        default:
            assert( NULL && "invalid attribute type!" );
    }

    return false;
}

void AttributeManager::removeAllAttributes()
{
	std::vector< EntityAttributeBase* >::iterator iter;
	for(iter=_attributes.begin();iter!=_attributes.end();++iter)
    {
		delete (*iter);
    }
    _attributes.clear();
}

AttributeManager& AttributeManager::operator = ( AttributeManager& attr )
{
    if ( &attr == this )
        return *this;

    // copy attribute values
    std::vector< EntityAttributeBase* >::iterator p_beg = attr.getAttributes().begin(), p_end = attr.getAttributes().end();
    for ( ; p_beg != p_end; p_beg++ )
    {
        setAttributeValue( ( *p_beg )->getName(), **p_beg );
    }

    return *this;
}


} // namespace hilife
