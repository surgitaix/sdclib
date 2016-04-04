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
 *  @file QName.h
 *  @project OSCLib
 *  @date 29.08.2011
 *  @author besting
 *  @copyright (c) SurgiTAIX AG
 */


#ifndef QNAME_H_
#define QNAME_H_

#include <atomic>
#include <string>
#include <vector>

namespace OSCLib {
namespace Data {

class QName;

typedef std::vector<Data::QName> QVector;

class QName {
public:
	static std::atomic<unsigned int> autoPrefix;

	QName();
	QName(const std::string & local, const std::string & ns);
	QName(const std::string & local, const std::string & ns, const std::string & prefix);
	~QName();

    const std::string & getLocal() const;
    void setLocal(const std::string & local);
    const std::string & getNamespace() const;
    const std::string & getPrefix() const;
    std::string getPrefixedName() const;
    void setNamespace(const std::string & ns);
    void setPrefix(const std::string & prefix);

    bool operator ==(const QName & qn) const;

private:
	std::string local;
	std::string prefix;
	std::string ns;
};

} /* namespace DPWS */
} /* namespace Data */
#endif /* QNAME_H_ */
