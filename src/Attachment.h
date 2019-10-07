#pragma once

#include "AttachmentInterfaces.h"

#include <vector>

namespace attachments {
	using byte_buffer = std::vector<std::uint8_t>;

	template<typename T>
	void* get_buffer( const T& t ) {
		return reinterpret_cast<void*>( const_cast<T*>( &t ) );
	}

	template<>
	void* get_buffer<byte_buffer>( const byte_buffer& t ) {
		return reinterpret_cast<void*>(const_cast<std::uint8_t*>(&t[0]));
	}

	template<typename T>
	std::size_t get_size( const T& t ) {
		return sizeof( T );
	}

	template<>
	std::size_t get_size<byte_buffer>( const byte_buffer& t ) {
		return t.size();
	}

	template<typename TStored>
	class TAttachment : public IAttachment {
	public:
		TAttachment( attachment_key key, const TStored& t )
			: m_Key( key )
			, m_Stored( t ) {
		}

		std::size_t GetSize() const override {
			return get_size( m_Stored );
		}

		void* GetBuffer() const override {
			return get_buffer( m_Stored );
		}

		attachment_key GetKey() const override {
			return m_Key;
		}

		TStored& GetValue() {
			return m_Stored;
		}
	protected:
		attachment_key m_Key{};
		TStored m_Stored{};
	};

	template<typename TStored>
	using TAttachmentPtr = std::shared_ptr<TAttachment<TStored>>;

	template<typename TStored>
	void operator >> ( TStored& t, IAttachmentPtr value ) {
		t = std::dynamic_pointer_cast<TAttachment<TStored>>( value )->GetValue();
	}

	template<typename TStored>
	void operator >> ( IAttachmentPtr value, TStored& t ) {
		t = std::dynamic_pointer_cast<TAttachment<TStored>>( value )->GetValue();
	}
} // attachments namespace