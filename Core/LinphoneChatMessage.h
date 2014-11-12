#pragma once

#include "LinphoneCore.h"
#include "LinphoneChatMessageListener.h"
#include "LinphoneChatRoom.h"
#include "Enums.h"

namespace Linphone
{
	namespace Core
	{
		ref class LinphoneCore;
		ref class LinphoneChatRoom;

		/// <summary>
		/// Represents a chat message shared between two users.
		/// </summary>
		public ref class LinphoneChatMessage sealed
		{
		public:
			/// <summary>
			/// Returns the text associated to this message.
			/// </summary>
			property Platform::String^ Text
			{
				Platform::String^ get();
			}
			
			/// <summary>
			/// Get peer address as LinphoneAddress associated to this message.
			/// </summary>
			property Linphone::Core::LinphoneAddress^ PeerAddress
			{
				Linphone::Core::LinphoneAddress^ get();
			}
			
			/// <summary>
			/// Get from address as LinphoneAddress associated to this message.
			/// </summary>
			property Linphone::Core::LinphoneAddress^ From
			{
				Linphone::Core::LinphoneAddress^ get();
			}
			
			/// <summary>
			/// Linphone message can carry external body as defined by rfc2017.
			/// </summary>
			property Platform::String^ ExternalBodyUrl
			{
				Platform::String^ get();
				void set(Platform::String^ value);
			}
			
			/// <summary>
			/// Gets the time at which the message was sent (in seconds since 01/01/1970).
			/// </summary>
			property int64 Time
			{
				int64 get();
			}

			/// <summary>
			/// Gets the state of the message (Idle, InProgress, Delivered or NotDelivered).
			/// </summary>
			property Linphone::Core::LinphoneChatMessageState State
			{
				Linphone::Core::LinphoneChatMessageState get();
			}

			/// <summary>
			/// Returns true if the message was outgoing, otherwise return false.
			/// </summary>
			property Platform::Boolean IsOutgoing
			{
				Platform::Boolean get();
			}

			/// <summary>
			/// Returns true if the message has been read, otherwise return false.
			/// </summary>
			property Platform::Boolean IsRead
			{
				Platform::Boolean get();
			}

			/// <summary>
			/// Returns the name of the file used in the file transfer if it exists
			/// </summary>
			property Platform::String^ FileTransferName
			{
				Platform::String^ get();
			}

			/// <summary>
			/// Gets the path to the file to read from or write to during the file transfer.
			/// </summary>
			property Platform::String^ FileTransferFilePath
			{
				Platform::String^ get();
			}

			/// <summary>
			/// Returns the content of the appData
			/// </summary>
			property Platform::String^ AppData
			{
				Platform::String^ get();
				void set(Platform::String^ value);
			}

			/// <summary>
			/// Starts the download of the image in the message if exists
			/// </summary>
			void StartFileDownload(Linphone::Core::LinphoneChatMessageListener^ listener, Platform::String^ filepath);

		private:
			friend class Linphone::Core::Utils;
			friend ref class Linphone::Core::LinphoneCore;
			friend ref class Linphone::Core::LinphoneChatRoom;

			LinphoneChatMessage(::LinphoneChatMessage *cm);
			~LinphoneChatMessage();

			::LinphoneChatMessage *message;
		};
	}
}