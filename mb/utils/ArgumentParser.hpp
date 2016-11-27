/*
* Copyright (c) 2016 maldicion069
*
* Authors: Cristian Rodríguez Bernal <ccrisrober@gmail.com>
*
* This file is part of MonkeyBrushPlusPlus <https://github.com/maldicion069/monkeybrushplusplus>
*
* This library is free software; you can redistribute it and/or modify it under
* the terms of the GNU Lesser General Public License version 3.0 as published
* by the Free Software Foundation.
*
* This library is distributed in the hope that it will be useful, but WITHOUT
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
* FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
* details.
*
* You should have received a copy of the GNU Lesser General Public License
* along with this library; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
*/

#ifndef __MB__ARGUMENT_PARSER__
#define __MB__ARGUMENT_PARSER__

#include <mb/api.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <iostream>
#include <sstream>

namespace MB
{
	class ArgumentParser;
	class OptionGroup;
	class Option;
	class Values;
	class Value;
	class Callback;

	typedef std::map<std::string, std::string> strMap;
	typedef std::map<std::string, std::list<std::string> > lstMap;
	typedef std::map<std::string, Option const*> optMap;

	const char* const SUPPRESS_HELP = "SUPPRESS" "HELP";
	const char* const SUPPRESS_USAGE = "SUPPRESS" "USAGE";

	//! Class for automatic conversion from string -> anytype
	class Value {
	public:
		MB_API
		Value() : str(), valid(false) {}
		MB_API
		Value(const std::string& v) : str(v), valid(true) {}
		MB_API
		operator const char*() { return str.c_str(); }
		MB_API
		operator bool() { bool t; return (valid && (std::istringstream(str) >> t)) ? t : false; }
		MB_API
		operator short() { short t; return (valid && (std::istringstream(str) >> t)) ? t : 0; }
		MB_API
		operator unsigned short() { unsigned short t; return (valid && (std::istringstream(str) >> t)) ? t : 0; }
		MB_API
		operator int() { int t; return (valid && (std::istringstream(str) >> t)) ? t : 0; }
		MB_API
		operator unsigned int() { unsigned int t; return (valid && (std::istringstream(str) >> t)) ? t : 0; }
		MB_API
		operator long() { long t; return (valid && (std::istringstream(str) >> t)) ? t : 0; }
		MB_API
		operator unsigned long() { unsigned long t; return (valid && (std::istringstream(str) >> t)) ? t : 0; }
		MB_API
		operator float() { float t; return (valid && (std::istringstream(str) >> t)) ? t : 0; }
		MB_API
		operator double() { double t; return (valid && (std::istringstream(str) >> t)) ? t : 0; }
		MB_API
		operator long double() { long double t; return (valid && (std::istringstream(str) >> t)) ? t : 0; }
	private:
		const std::string str;
		bool valid;
	};

	class Values {
	public:
		MB_API
		Values() : _map() {}
		MB_API
		const std::string& operator[] (const std::string& d) const;
		MB_API
		std::string& operator[] (const std::string& d) { return _map[d]; }
		MB_API
		bool is_set(const std::string& d) const { return _map.find(d) != _map.end(); }
		MB_API
		bool is_set_by_user(const std::string& d) const { return _userSet.find(d) != _userSet.end(); }
		MB_API
		void is_set_by_user(const std::string& d, bool yes);
		MB_API
		Value get(const std::string& d) const { return (is_set(d)) ? Value((*this)[d]) : Value(); }

		typedef std::list<std::string>::iterator iterator;
		typedef std::list<std::string>::const_iterator const_iterator;
		std::list<std::string>& all(const std::string& d) { return _appendMap[d]; }
		const std::list<std::string>& all(const std::string& d) const { return _appendMap.find(d)->second; }

	private:
		strMap _map;
		lstMap _appendMap;
		std::set<std::string> _userSet;
	};

	class OptionContainer {
	public:
		MB_API
		OptionContainer(const std::string& d = "") : _description(d) {}
		MB_API
		virtual ~OptionContainer() {}

		MB_API
		virtual OptionContainer& description(const std::string& d) { _description = d; return *this; }
		MB_API
		virtual const std::string& description() const { return _description; }

		MB_API
		Option& add_option(const std::string& opt);
		MB_API
		Option& add_option(const std::string& opt1, const std::string& opt2);
		MB_API
		Option& add_option(const std::string& opt1, const std::string& opt2, const std::string& opt3);
		MB_API
		Option& add_option(const std::vector<std::string>& opt);

		MB_API
		std::string format_option_help(unsigned int indent = 2) const;

	protected:
		std::string _description;

		std::list<Option> _opts;
		optMap _optmap_s;
		optMap _optmap_l;

	private:
		virtual const ArgumentParser& get_parser() = 0;
	};

	class ArgumentParser : public OptionContainer {
	public:
		MB_API
		ArgumentParser();
		MB_API
		virtual ~ArgumentParser() {}

		MB_API
		ArgumentParser& usage(const std::string& u) { set_usage(u); return *this; }
		MB_API
		ArgumentParser& version(const std::string& v) { _version = v; return *this; }
		MB_API
		ArgumentParser& description(const std::string& d) { _description = d; return *this; }
		MB_API
		ArgumentParser& add_help_option(bool h) { _add_help_option = h; return *this; }
		MB_API
		ArgumentParser& add_version_option(bool v) { _add_version_option = v; return *this; }
		MB_API
		ArgumentParser& prog(const std::string& p) { _prog = p; return *this; }
		MB_API
		ArgumentParser& epilog(const std::string& e) { _epilog = e; return *this; }
		MB_API
		ArgumentParser& set_defaults(const std::string& dest, const std::string& val) {
			_defaults[dest] = val; return *this;
		}
		template<typename T>
		ArgumentParser& set_defaults(const std::string& dest, T t) { std::ostringstream ss; ss << t; _defaults[dest] = ss.str(); return *this; }
		ArgumentParser& enable_interspersed_args() { _interspersed_args = true; return *this; }
		ArgumentParser& disable_interspersed_args() { _interspersed_args = false; return *this; }
		ArgumentParser& add_option_group(const OptionGroup& group);

		MB_API
		const std::string& usage() const { return _usage; }
		MB_API
		const std::string& version() const { return _version; }
		MB_API
		const std::string& description() const { return _description; }
		MB_API
		bool add_help_option() const { return _add_help_option; }
		MB_API
		bool add_version_option() const { return _add_version_option; }
		MB_API
		const std::string& prog() const { return _prog; }
		MB_API
		const std::string& epilog() const { return _epilog; }
		MB_API
		bool interspersed_args() const { return _interspersed_args; }

		MB_API
		Values& parse_args(int argc, char const* const* argv);
		MB_API
		Values& parse_args(const std::vector<std::string>& args);
		template<typename InputIterator>
		Values& parse_args(InputIterator begin, InputIterator end) {
			return parse_args(std::vector<std::string>(begin, end));
		}

		MB_API
		const std::list<std::string>& args() const { return _leftover; }
		MB_API
		std::vector<std::string> args() {
			return std::vector<std::string>(_leftover.begin(), _leftover.end());
		}

		MB_API
		std::string format_help() const;
		MB_API
		void print_help() const;

		MB_API
		void set_usage(const std::string& u);
		MB_API
		std::string get_usage() const;
		MB_API
		void print_usage(std::ostream& out) const;
		MB_API
		void print_usage() const;

		MB_API
		std::string get_version() const;
		MB_API
		void print_version(std::ostream& out) const;
		MB_API
		void print_version() const;

		MB_API
		void error(const std::string& msg) const;
		MB_API
		void exit() const;

	private:
		const ArgumentParser& get_parser() { return *this; }
		const Option& lookup_short_opt(const std::string& opt) const;
		const Option& lookup_long_opt(const std::string& opt) const;

		void handle_short_opt(const std::string& opt, const std::string& arg);
		void handle_long_opt(const std::string& optstr);

		void process_opt(const Option& option, const std::string& opt, const std::string& value);

		std::string format_usage(const std::string& u) const;

		std::string _usage;
		std::string _version;
		bool _add_help_option;
		bool _add_version_option;
		std::string _prog;
		std::string _epilog;
		bool _interspersed_args;

		Values _values;

		strMap _defaults;
		std::list<OptionGroup const*> _groups;

		std::list<std::string> _remaining;
		std::list<std::string> _leftover;

		friend class Option;
	};

	class OptionGroup : public OptionContainer {
	public:
		MB_API
		OptionGroup(const ArgumentParser& p, const std::string& t, const std::string& d = "") :
			OptionContainer(d), _parser(p), _title(t) {}
		MB_API
		virtual ~OptionGroup() {}

		MB_API
		OptionGroup& title(const std::string& t) { _title = t; return *this; }
		MB_API
		const std::string& title() const { return _title; }

	private:
		const ArgumentParser& get_parser() { return _parser; }

		const ArgumentParser& _parser;
		std::string _title;

		friend class ArgumentParser;
	};

	class Option {
	public:
		MB_API
		Option(const ArgumentParser& p) :
			_parser(p), _action("store"), _type("string"), _nargs(1), _callback(0) {}
		MB_API
		virtual ~Option() {}

		MB_API
		Option& action(const std::string& a);
		MB_API
		Option& type(const std::string& t);
		MB_API
		Option& dest(const std::string& d) { _dest = d; return *this; }
		MB_API
		Option& set_default(const std::string& d) { _default = d; return *this; }
		template<typename T>
		Option& set_default(T t) { std::ostringstream ss; ss << t; _default = ss.str(); return *this; }
		MB_API
		Option& nargs(size_t n) { _nargs = n; return *this; }
		MB_API
		Option& set_const(const std::string& c) { _const = c; return *this; }
		template<typename InputIterator>
		Option& choices(InputIterator begin, InputIterator end) {
			_choices.assign(begin, end); type("choice"); return *this;
		}
#if __cplusplus >= 201103L
		MB_API
		Option& choices(std::initializer_list<std::string> ilist) {
			_choices.assign(ilist); type("choice"); return *this;
		}
#endif
		MB_API
		Option& help(const std::string& h) { _help = h; return *this; }
		MB_API
		Option& metavar(const std::string& m) { _metavar = m; return *this; }
		MB_API
		Option& callback(Callback& c) { _callback = &c; return *this; }

		const std::string& action() const { return _action; }
		MB_API
		const std::string& type() const { return _type; }
		MB_API
		const std::string& dest() const { return _dest; }
		MB_API
		const std::string& get_default() const;
		MB_API
		size_t nargs() const { return _nargs; }
		MB_API
		const std::string& get_const() const { return _const; }
		MB_API
		const std::list<std::string>& choices() const { return _choices; }
		MB_API
		const std::string& help() const { return _help; }
		MB_API
		const std::string& metavar() const { return _metavar; }
		MB_API
		Callback* callback() const { return _callback; }

	private:
		std::string check_type(const std::string& opt, const std::string& val) const;
		std::string format_option_help(unsigned int indent = 2) const;
		std::string format_help(unsigned int indent = 2) const;

		const ArgumentParser& _parser;

		std::set<std::string> _short_opts;
		std::set<std::string> _long_opts;

		std::string _action;
		std::string _type;
		std::string _dest;
		std::string _default;
		size_t _nargs;
		std::string _const;
		std::list<std::string> _choices;
		std::string _help;
		std::string _metavar;
		Callback* _callback;

		friend class OptionContainer;
		friend class ArgumentParser;
	};

	class Callback {
	public:
		MB_API
		virtual void operator() (const Option& option, const std::string& opt, const std::string& val, const ArgumentParser& parser) = 0;
		MB_API
		virtual ~Callback() {}
	};

}

#endif /* __MB__ARGUMENT_PARSER__ */