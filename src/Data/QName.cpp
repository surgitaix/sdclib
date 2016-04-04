/**
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * (at your option) any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  */

/**
 *  @file QName.cpp
 *  @project OSCLib
 *  @date 29.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#include "OSCLib/Data/QName.h"

namespace OSCLib {
namespace Data {

std::atomic<unsigned int> QName::autoPrefix(1);

QName::QName() : prefix("i" + std::to_string(autoPrefix++))
{
}

QName::QName(const std::string & local, const std::string & ns) :
		local(local),
		prefix("i" + std::to_string(autoPrefix++)),
		ns(ns)
{
}

QName::QName(const std::string & local, const std::string & ns, const std::string & prefix) :
				local(local),
				prefix(prefix),
				ns(ns)
{
}

QName::~QName()
{
}

std::string QName::getPrefixedName() const {
	return getPrefix() + ":" + getLocal();
}

const std::string & QName::getLocal() const {
	return local;
}

void QName::setLocal(const std::string & local) {
	this->local = local;
}

const std::string & QName::getNamespace() const {
	return ns;
}

const std::string & QName::getPrefix() const {
	return prefix;
}

void QName::setNamespace(const std::string & ns) {
	this->ns = ns;
}

void QName::setPrefix(const std::string & prefix) {
	this->prefix = prefix;
}

bool QName::operator ==(const QName & qn) const {
	return (qn.getLocal().compare(getLocal()) == 0)	&& (qn.getNamespace().compare(getNamespace()) == 0);
}

} /* namespace DPWS */
} /* namespace Data */
