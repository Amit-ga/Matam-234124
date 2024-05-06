#ifndef FESTIVAL_H
#define FESTIVAL_H

#include "event_container.h"

namespace mtm
{
	class Festival : public EventContainer
	{
		DateWrap event_date;

	public:
		explicit Festival(const DateWrap date);
		//Iterator's value is undefined after this operation.
		void add(const BaseEvent& event) override;
		/*destructor*/
		virtual ~Festival() = default;
	};
}

#endif //FESTIVAL_H
