#include "stdafx.h"
#include "MyString.h"

CMyString::CMyString(std::unique_ptr<char[]> && memoryBlock, size_t len)
{
	m_bufferPtr = std::move(memoryBlock);
	m_bufferPtr[len] = '\0';
	m_length = len;
}

CMyString::CMyString(const char * pString)
{
	size_t length;
	if (pString && (length = strlen(pString)) > 0)
	{
		m_bufferPtr = std::unique_ptr<char[]>(new char[length + 1]);
		memcpy(m_bufferPtr.get(), pString, (length + 1));
		m_length = length;
	}
}

CMyString::CMyString(const char * pString, size_t length)
{
	if (pString && length > 0)
	{
		m_bufferPtr = std::unique_ptr<char[]>(new char[length + 1]);
		memcpy(m_bufferPtr.get(), pString, length);
		m_length = length;
		m_bufferPtr.get()[m_length] = '\0';
	}
}

CMyString::CMyString(const CMyString & other)
{
	if (other.GetLength() > 0)
	{
		m_bufferPtr = std::unique_ptr<char[]>(new char[other.GetLength() + 1]);
		memcpy(m_bufferPtr.get(), other.GetStringData(), other.GetLength());
		m_length = other.GetLength();
	}
}

CMyString::CMyString(CMyString && other)
{
	if (other.GetLength() > 0)
	{
		CMyString EmptyStr("");
		m_length = other.GetLength();
		m_bufferPtr = move(other.m_bufferPtr);
		other = EmptyStr;
	}
}

CMyString::CMyString(const std::string & stlString)
{
	if (stlString.length() > 0)
	{
		m_bufferPtr = std::unique_ptr<char[]>(new char[stlString.length() + 1]);
		memcpy(m_bufferPtr.get(), stlString.c_str(), stlString.length() + 1);
		m_length = stlString.length();
	}
}

const char * CMyString::GetStringData() const
{
	if (m_bufferPtr.get())
	{
		return m_bufferPtr.get();
	}
	return &CMyString::m_emptyStr;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	length = length < m_length ? length : m_length;
	if ((m_length - start) >= length && start < m_length)
	{
		return CMyString(m_bufferPtr.get() + start, length);
	}
	return CMyString();
}

size_t CMyString::GetLength() const
{
	return m_length;
}

void CMyString::Clear()
{
	m_bufferPtr = nullptr;
	m_length = 0;
}

CMyString & CMyString::operator=(const CMyString & arg)
{
	if (&arg != this)
	{
		if (arg.GetLength() > 0)
		{
			std::unique_ptr<char[]> bufferTempPtr(new char[arg.GetLength() + 1]);
			m_length = arg.GetLength();
			m_bufferPtr = std::move(bufferTempPtr);
			memcpy(m_bufferPtr.get(), arg.GetStringData(), m_length + 1);
		}
		else
		{
			Clear();
		}
	}
	return *this;
}

CMyString & CMyString::operator=(CMyString && arg)
{
	if (&arg != this)
	{
		Clear();
		if (arg.GetLength() > 0)
		{
			CMyString emptyStr("");
			m_length = arg.GetLength();
			m_bufferPtr = std::move(arg.m_bufferPtr);
			arg = emptyStr;
		}
	}
	return *this;
}

CMyString operator+(const CMyString & arg1, const CMyString & arg2)
{
	size_t newStrLen = arg1.GetLength() + arg2.GetLength();
	std::unique_ptr<char[]> temp(new char[newStrLen + 1]);
	memcpy(temp.get(), arg1.GetStringData(), arg1.GetLength());
	memcpy(temp.get() + arg1.GetLength(), arg2.GetStringData(), arg2.GetLength());
	CMyString tempString(std::move(temp), newStrLen);
	return tempString;
}

CMyString & CMyString::operator+=(const CMyString & arg)
{
	*this = *this + arg;
	return *this;
}

char & CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw std::logic_error("incorrect index");
	}
	return m_bufferPtr[index];
};

const char & CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw std::logic_error("incorrect index");
	}
	return m_bufferPtr[index];
}

bool operator==(const CMyString & arg1, const CMyString & arg2)
{
	if (arg1.GetLength() == arg2.GetLength())
	{
		for (size_t i = 0; i < arg2.GetLength(); ++i)
		{
			if (arg1[i] != arg2[i])
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool operator<(const CMyString & arg1, const CMyString & arg2)
{
	size_t length = std::min(arg1.GetLength(), arg2.GetLength());
	auto memCompareResult = memcmp(arg1.GetStringData(), arg2.GetStringData(), length);
	return memCompareResult < 0 || memCompareResult == 0 && arg1.GetLength() < arg2.GetLength();
}

bool operator<=(const CMyString & arg1, const CMyString & arg2)
{
	size_t length = std::min(arg1.GetLength(), arg2.GetLength());
	auto memCompareResult = memcmp(arg1.GetStringData(), arg2.GetStringData(), length);
	return memCompareResult < 0 || memCompareResult == 0 && arg1.GetLength() <= arg2.GetLength();
}

bool operator>(const CMyString & arg1, const CMyString & arg2)
{
	return !(arg1 <= arg2);
}

bool operator>=(const CMyString & arg1, const CMyString & arg2)
{
	return !(arg1 < arg2);
}

bool operator!=(const CMyString & arg1, const CMyString & arg2)
{
	return !(arg1 == arg2);
}

CMyString::CIterator<char> CMyString::begin() const
{
	char * end = m_bufferPtr.get() + m_length;
	return CMyString::CIterator<char>(m_bufferPtr.get(), m_bufferPtr.get(), end);
}

CMyString::CIterator<char> CMyString::end() const
{
	char * end = m_bufferPtr.get() + m_length;
	return CMyString::CIterator<char>(end, m_bufferPtr.get(), end);
}

CMyString::CIterator<const char> CMyString::cbegin() const
{
	char * end = m_bufferPtr.get() + m_length;
	return CMyString::CIterator<const char>(m_bufferPtr.get(), m_bufferPtr.get(), end);
}

CMyString::CIterator<const char> CMyString::cend() const
{
	char * end = m_bufferPtr.get() + m_length;
	return CMyString::CIterator<const char>(end, m_bufferPtr.get(), end);
}