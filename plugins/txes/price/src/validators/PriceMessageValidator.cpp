/**
*** Copyright (c) 2016-2019, Jaguar0625, gimre, BloodyRookie, Tech Bureau, Corp.
*** Copyright (c) 2020-present, Jaguar0625, gimre, BloodyRookie.
*** All rights reserved.
***
*** This file is part of Catapult.
***
*** Catapult is free software: you can redistribute it and/or modify
*** it under the terms of the GNU Lesser General Public License as published by
*** the Free Software Foundation, either version 3 of the License, or
*** (at your option) any later version.
***
*** Catapult is distributed in the hope that it will be useful,
*** but WITHOUT ANY WARRANTY; without even the implied warranty of
*** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
*** GNU Lesser General Public License for more details.
***
*** You should have received a copy of the GNU Lesser General Public License
*** along with Catapult. If not, see <http://www.gnu.org/licenses/>.
**/

#include "Validators.h"

namespace catapult { namespace validators {

	using Notification = model::PriceMessageNotification;

	DECLARE_STATELESS_VALIDATOR(PriceMessage, Notification)() {
		return MAKE_STATELESS_VALIDATOR(PriceMessage, [](const Notification& notification) {
			if (!notification.lowPrice) {
				if (!notification.highPrice) {
					return Failure_Price_lowPrice_and_highPrice_not_set;
				}
				return Failure_Price_lowPrice_not_set;
			} else if (!notification.highPrice) {
				return Failure_Price_highPrice_not_set;
			} else if (notification.lowPrice > notification.highPrice) {
				return Failure_Price_lowPrice_is_higher_than_highPrice;
			}
			return ValidationResult::Success;
		});
	}
}}
