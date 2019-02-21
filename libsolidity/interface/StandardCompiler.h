/*
	This file is part of solidity.

	solidity is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	solidity is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with solidity.  If not, see <http://www.gnu.org/licenses/>.
*/
/**
 * @author Alex Beregszaszi
 * @date 2016
 * Standard JSON compiler interface.
 */

#pragma once

#include <libsolidity/interface/CompilerStack.h>

#include <boost/optional.hpp>

namespace dev
{

namespace solidity
{

/**
 * Standard JSON compiler interface, which expects a JSON input and returns a JSON output.
 * See docs/using-the-compiler#compiler-input-and-output-json-description.
 */
class StandardCompiler: boost::noncopyable
{
public:
	/// Creates a new StandardCompiler.
	/// @param _readFile callback to used to read files for import statements. Must return
	/// and must not emit exceptions.
	explicit StandardCompiler(ReadCallback::Callback const& _readFile = ReadCallback::Callback())
		: m_compilerStack(_readFile), m_readFile(_readFile)
	{
	}

	/// Sets all input parameters according to @a _input which conforms to the standardized input
	/// format, performs compilation and returns a standardized output.
	Json::Value compile(Json::Value const& _input) noexcept;
	/// Parses input as JSON and peforms the above processing steps, returning a serialized JSON
	/// output. Parsing errors are returned as regular errors.
	std::string compile(std::string const& _input) noexcept;

private:
	/// Validaes and applies the optimizer settings.
	/// On error returns the json-formatted error message.
	boost::optional<Json::Value> parseOptimizerSettings(Json::Value const& _settings);

	Json::Value compileInternal(Json::Value const& _input);

	CompilerStack m_compilerStack;
	ReadCallback::Callback m_readFile;
};

}
}
