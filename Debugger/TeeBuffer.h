#include <iostream>
#include <fstream>
#include <streambuf>

namespace Debugger
{
	template <class CharType, class Traits = std::char_traits<CharType>>
	class TeeBuffer : public std::basic_streambuf<CharType, Traits>
	{
	public:
		typedef CharType char_type;
		typedef typename Traits::int_type int_type;
		typedef typename Traits::pos_type pos_type;
		typedef typename Traits::off_type off_type;
		typedef Traits traits_type;
		typedef std::basic_streambuf<CharType, Traits> streambuf_type;

	private:
		streambuf_type* streamBuffer1;
		streambuf_type* streamBuffer2;
		char_type*		buffer;

		enum {BUFFER_SIZE = 4096 / sizeof(char_type)};

	public:
		TeeBuffer(streambuf_type* sbuf1, streambuf_type* sbuf2)
			: streamBuffer1(sbuf1), streamBuffer2(sbuf2), buffer(new char_type[BUFFER_SIZE])
		{
			setp(buffer, buffer + BUFFER_SIZE);
		}

		~TeeBuffer()
		{
			pubsync();
			delete[] buffer;
		}

	protected:
		virtual int_type overflow(int_type c = traits_type::eof())
		{
			// empty our buffer into m_sbuf1 and m_sbuf2
			std::streamsize n = static_cast<std::streamsize>(pptr() - pbase());
			std::streamsize size1 = streamBuffer1->sputn(pbase(), n);
			std::streamsize size2 = streamBuffer2->sputn(pbase(), n);

			if (size1 != n || size2 != n)
			{
				return traits_type::eof();
			}

			// reset our buffer
			setp(buffer, buffer + BUFFER_SIZE);

			// write the passed character if necessary
			if (!traits_type::eq_int_type(c, traits_type::eof()))
			{
				traits_type::assign(*pptr(), traits_type::to_char_type(c));
				pbump(1);
			}

			return traits_type::not_eof(c);
		}

		virtual int sync()
		{
			// flush our buffer into streamBuffer1 and streamBuffer2
			int_type c = overflow(traits_type::eof());

			// checking return for eof.
			if (traits_type::eq_int_type(c, traits_type::eof()))
			{
				return -1;
			}

			// flush streamBuffer1 and streamBuffer2
			if (streamBuffer1->pubsync() == -1 || streamBuffer2->pubsync() == -1)
			{
				return -1;
			}

			return 0;
		}
	};

	typedef TeeBuffer<char>    teebuf;
	typedef TeeBuffer<wchar_t> wteebuf;

	template <class CharType, class Traits = std::char_traits<CharType> >
	struct scoped_basic_streambuf_assignment
	{
		typedef std::basic_ostream<CharType, Traits> ostream_type;
		typedef std::basic_streambuf<CharType, Traits> streambuf_type;

		ostream_type&	streamType;
		streambuf_type*	streamBufferType;

		scoped_basic_streambuf_assignment(ostream_type& _streamType, streambuf_type* _streamBufferType) 
			: streamType(_streamType)
		{
			streamBufferType = _streamType.rdbuf(_streamBufferType);
		}

		~scoped_basic_streambuf_assignment()
		{
			streamType.rdbuf(streamBufferType);
		}
	};

	typedef scoped_basic_streambuf_assignment<char>    scoped_streambuf_assignment;
	typedef scoped_basic_streambuf_assignment<wchar_t> scoped_wstreambuf_assignment;
}