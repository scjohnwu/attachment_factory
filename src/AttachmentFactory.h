#pragma once

#include "Attachment.h"

#include <typeindex>
#include <map>

namespace attachments {
	

	class CAttachmentFactory {
	public:
		template<typename TStored>
		bool RegisterType( attachment_key key ) {
			auto id = typeid( TStored ).hash_code();

			// can't register byte_buffer
			if ( id == typeid( byte_buffer ).hash_code() ) {
				return false;
			}

			// can't register type twice
			if ( m_KeyMapping.find( id ) != std::end( m_KeyMapping ) ) {
				return false;
			}

			m_KeyMapping[id] = key;

			return true;
		}


		template<typename TStored>
		IAttachment* CreateAttachment( const TStored& stored ) {
			auto key_iter = m_KeyMapping.find( typeid( stored ).hash_code() );

			if ( key_iter == std::end( m_KeyMapping ) ) {
				throw "unregisterd type";
			}

			return new TAttachment<TStored>( key_iter->second, stored );
		};

		// any key can be used, it's freeform
		IAttachment* CreateAttachment( attachment_key key, const std::uint8_t* data, std::size_t size ) {
			byte_buffer storage{ data, data + size };

			// It's either possible to ban keys or to add separte storage for raw keys

			return new TAttachment<byte_buffer>( key, storage );
		}

		std::vector<attachment_key> GetKeys() const {
			std::vector<attachment_key> result;

			for ( auto& value : m_KeyMapping ) {
				result.push_back( value.second );
			}

			return result;
		}

	protected:
		std::map<std::size_t, attachment_key> m_KeyMapping;
	};
}