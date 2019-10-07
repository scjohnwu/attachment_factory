#pragma once

#include <map>
#include <memory>

namespace attachments {
	using attachment_key = std::uint64_t;

	struct IAttachment {
		virtual std::size_t GetSize() const = 0;
		virtual void* GetBuffer() const = 0;

		virtual attachment_key GetKey() const = 0;

		virtual ~IAttachment() = default;
	};
	using IAttachmentPtr = std::shared_ptr<IAttachment>;

	struct IAttachmentContainer {
		virtual void Attach(attachment_key, IAttachmentPtr) = 0;

		virtual ~IAttachmentContainer() = default;
	};
} // attachments namespace
