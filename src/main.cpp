#include "AttachmentFactory.h"

#include <iostream>

// User type for experiments
struct MyType {
	int a{ 3 };
	int b{ 4 };
};

int main() {
	using namespace attachments;
	// Store keys
	CAttachmentFactory factory;

	// Static initialization
	const attachment_key key = 89321;
	factory.RegisterType<MyType>( key );

	// Variable to store
	MyType my_variable;
	my_variable.a = 33;
	my_variable.b = 66;

	// Attachment creation
	IAttachmentPtr some_attachment{ factory.CreateAttachment( my_variable ) };

	// Variable acquisition
	// Typed, it's assumed that you know the type related to the key
	MyType out_variable;
	some_attachment >> out_variable;

	std::cout << out_variable.a << "\n";
	std::cout << out_variable.b << "\n";
	std::cout << some_attachment->GetKey() << "\n";

	// Hacking through raw pointer
	MyType* ref_variable = reinterpret_cast<MyType*>( some_attachment->GetBuffer() );
	
	std::cout << ref_variable->a << "\n";
	std::cout << ref_variable->b << "\n";

	// Raw buffer
	const attachment_key another_key = 4739;
	std::uint8_t some_buffer[4] = { 49, 49, 49, 49 };

	IAttachmentPtr another_attachment{ factory.CreateAttachment( key, some_buffer, sizeof( some_buffer ) ) };

	// Iterate over raw buffer
	uint8_t* pointer = reinterpret_cast<uint8_t*>( another_attachment->GetBuffer() );
	for ( int i = 0; i < another_attachment->GetSize(); ++i ) {
		std::cout << pointer[i] << " ";
	}
	std::cout << "\n";

	return 0;
}