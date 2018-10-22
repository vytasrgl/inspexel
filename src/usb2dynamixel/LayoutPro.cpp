#include "LayoutPro.h"

namespace dynamixel::pro {

auto MotorLayoutInfo::getInfos() -> meta::Layout<Register> const& {
	using A = meta::LayoutField::Access;
	static auto data = meta::Layout<Register> {
		{Register::MODEL_NUMBER           , {2, true,  A:: R, "Model Number"           , "Model Number"           }},
		{Register::MODEL_INFORMATION      , {4, true,  A:: R, "Model Information"      , "Model Information"      }},
		{Register::FIRMWARE_VERSION       , {1, true,  A:: R, "Firmware Version"       , "Firmware Version"       }},
		{Register::ID                     , {1, true,  A::RW, "ID"                     , "ID"                     }},
		{Register::BAUD_RATE              , {1, true,  A::RW, "Baud Rate"              , "Baud Rate"              }},
		{Register::RETURN_DELAY_TIME      , {1, true,  A::RW, "Return Delay Time"      , "Return Delay Time"      }},
		{Register::OPERATING_MODE         , {1, true,  A::RW, "Operating Mode"         , "Operating Mode"         }},
		{Register::HOMING_OFFSET          , {4, true,  A::RW, "Homing Offset"          , "Homing Offset"          }},
		{Register::MOVING_THRESHOLD       , {4, true,  A::RW, "Moving Threshold"       , "Moving Threshold"       }},
		{Register::TEMPERATURE_LIMIT      , {1, true,  A::RW, "Temperature Limit"      , "Temperature Limit"      }},
		{Register::MAX_VOLTAGE_LIMIT      , {2, true,  A::RW, "Max Voltage Limit"      , "Max Voltage Limit"      }},
		{Register::MIN_VOLTAGE_LIMIT      , {2, true,  A::RW, "Min Voltage Limit"      , "Min Voltage Limit"      }},
		{Register::ACCELERATION_LIMIT     , {4, true,  A::RW, "Acceleration Limit"     , "Acceleration Limit"     }},
		{Register::TORQUE_LIMIT           , {2, true,  A::RW, "Torque Limit"           , "Torque Limit"           }},
		{Register::VELOCITY_LIMIT         , {4, true,  A::RW, "Velocity Limit"         , "Velocity Limit"         }},
		{Register::MAX_POSITION_LIMIT     , {4, true,  A::RW, "Max Position Limit"     , "Max Position Limit"     }},
		{Register::MIN_POSITION_LIMIT     , {4, true,  A::RW, "Min Position Limit"     , "Min Position Limit"     }},
		{Register::EXTERNAL_PORT_MODE_1   , {1, true,  A::RW, "External Port Mode 1"   , "External Port Mode 1"   }},
		{Register::EXTERNAL_PORT_MODE_2   , {1, true,  A::RW, "External Port Mode 2"   , "External Port Mode 2"   }},
		{Register::EXTERNAL_PORT_MODE_3   , {1, true,  A::RW, "External Port Mode 3"   , "External Port Mode 3"   }},
		{Register::EXTERNAL_PORT_MODE_4   , {1, true,  A::RW, "External Port Mode 4"   , "External Port Mode 4"   }},
		{Register::SHUTDOWN               , {1, true,  A::RW, "Shutdown"               , "Shutdown"               }},
		{Register::INDIRECT_ADDRESS_BLOCK , {512, true, A::RW, "Indirect Addresses Block", "Indirect Addresses Block"}},
		{Register::TORQUE_ENABLE          , {1, false, A::RW, "Torque Enable"          , "Torque Enable"          }},
		{Register::LED_RED                , {1, false, A::RW, "LED Red"                , "LED Red"                }},
		{Register::LED_GREEN              , {1, false, A::RW, "LED Green"              , "LED Green"              }},
		{Register::LED_BLUE               , {1, false, A::RW, "LED Blue"               , "LED Blue"               }},
		{Register::VELOCITY_I_GAIN        , {2, false, A::RW, "Velocity I Gain"        , "Velocity I Gain"        }},
		{Register::VELOCITY_P_GAIN        , {2, false, A::RW, "Velocity P Gain"        , "Velocity P Gain"        }},
		{Register::POSITION_P_GAIN        , {2, false, A::RW, "Position P Gain"        , "Position P Gain"        }},
		{Register::GOAL_POSITION          , {4, false, A::RW, "Goal Position"          , "Goal Position"          }},
		{Register::GOAL_VELOCITY          , {4, false, A::RW, "Goal Velocity"          , "Goal Velocity"          }},
		{Register::GOAL_TORQUE            , {2, false, A::RW, "Goal Torque"            , "Goal Torque"            }},
		{Register::GOAL_ACCELERATION      , {4, false, A::RW, "Goal Acceleration"      , "Goal Acceleration"      }},
		{Register::MOVING                 , {1, false, A:: R, "Moving"                 , "Moving"                 }},
		{Register::PRESENT_POSITION       , {4, false, A:: R, "Present Position"       , "Present Position"       }},
		{Register::PRESENT_VELOCITY       , {4, false, A:: R, "Present Velocity"       , "Present Velocity"       }},
		{Register::PRESENT_CURRENT        , {2, false, A:: R, "Present Current"        , "Present Current"        }},
		{Register::PRESENT_INPUT_VOLTAGE  , {2, false, A:: R, "Present Input_voltage"  , "Present Input_voltage"  }},
		{Register::PRESENT_TEMPERATURE    , {1, false, A:: R, "Present Temperature"    , "Present Temperature"    }},
		{Register::EXTERNAL_PORT_DATA_1   , {2, false, A::RW, "External Port Data 1"   , "External Port Data 1"   }},
		{Register::EXTERNAL_PORT_DATA_2   , {2, false, A::RW, "External Port Data 2"   , "External Port Data 2"   }},
		{Register::EXTERNAL_PORT_DATA_3   , {2, false, A::RW, "External Port Data 3"   , "External Port Data 3"   }},
		{Register::EXTERNAL_PORT_DATA_4   , {2, false, A::RW, "External Port Data 4"   , "External Port Data 4"   }},
		{Register::REGISTERED_INSTRUCTION , {1, false, A:: R, "Registered Instruction" , "Registered Instruction" }},
		{Register::STATUS_RETURN_LEVEL    , {1, false, A::RW, "Status Return Level"    , "Status Return Level"    }},
		{Register::HARDWARE_ERROR_STATUS  , {1, false, A:: R, "Hardware Error Status"  , "Hardware Error Status"  }},
		{Register::INDIRECT_DATA_BLOCK ,    {256, false, A::RW, "Indirect Data Block", "Indirect Data Block"}},
	};
	return data;
}

auto MotorLayoutInfo::getDefaults() -> std::map<uint32_t, meta::Info<Register>> const& {
	static auto data = std::map<uint32_t, meta::Info<Register>> {
		{46'352, {
			46'352,
			LayoutType::Pro,
			"M54-60-S250-R",
			{"M54-60-S250-R"},
			meta::buildConverters(251'417, 0, 0.00397746), {
				{Register::MODEL_NUMBER           ,   46'352},
				{Register::MODEL_INFORMATION      ,       {}},
				{Register::FIRMWARE_VERSION       ,       {}},
				{Register::ID                     ,        1},
				{Register::BAUD_RATE              ,        1},
				{Register::RETURN_DELAY_TIME      ,      250},
				{Register::OPERATING_MODE         ,        3},
				{Register::HOMING_OFFSET          ,        0},
				{Register::MOVING_THRESHOLD       ,       50},
				{Register::TEMPERATURE_LIMIT      ,       80},
				{Register::MAX_VOLTAGE_LIMIT      ,      400},
				{Register::MIN_VOLTAGE_LIMIT      ,      150},
				{Register::ACCELERATION_LIMIT     ,        {}},
				{Register::TORQUE_LIMIT           ,       180},
				{Register::VELOCITY_LIMIT         ,     8'000},
				{Register::MAX_POSITION_LIMIT     ,   125'708},
				{Register::MIN_POSITION_LIMIT     ,  -125'708},
				{Register::EXTERNAL_PORT_MODE_1   ,         0},
				{Register::EXTERNAL_PORT_MODE_2   ,         0},
				{Register::EXTERNAL_PORT_MODE_3   ,         0},
				{Register::EXTERNAL_PORT_MODE_4   ,         0},
				{Register::SHUTDOWN               ,        58},
				{Register::TORQUE_ENABLE          ,         0},
				{Register::LED_RED                ,         0},
				{Register::LED_GREEN              ,         0},
				{Register::LED_BLUE               ,         0},
				{Register::VELOCITY_I_GAIN        ,        16},
				{Register::VELOCITY_P_GAIN        ,       256},
				{Register::POSITION_P_GAIN        ,        32},
				{Register::GOAL_POSITION          ,        {}},
				{Register::GOAL_VELOCITY          ,         0},
				{Register::GOAL_TORQUE            ,         0},
				{Register::GOAL_ACCELERATION      ,         0},
				{Register::MOVING                 ,        {}},
				{Register::PRESENT_POSITION       ,        {}},
				{Register::PRESENT_VELOCITY       ,        {}},
				{Register::PRESENT_CURRENT        ,        {}},
				{Register::PRESENT_INPUT_VOLTAGE  ,        {}},
				{Register::PRESENT_TEMPERATURE    ,        {}},
				{Register::EXTERNAL_PORT_DATA_1   ,         0},
				{Register::EXTERNAL_PORT_DATA_2   ,         0},
				{Register::EXTERNAL_PORT_DATA_3   ,         0},
				{Register::EXTERNAL_PORT_DATA_4   ,         0},
				{Register::REGISTERED_INSTRUCTION ,         0},
				{Register::STATUS_RETURN_LEVEL    ,         2},
				{Register::HARDWARE_ERROR_STATUS  ,         0},
			}
		}}
	};
	auto newMotor = [&](int number, std::string shortName, std::vector<std::string> names) -> meta::Info<Register>& {
		auto& m = data[number];
		m = data.at(46'352);
		m.modelNumber = number;
		m.shortName = std::move(shortName);
		m.motorNames = std::move(names);
		m.defaultLayout[Register::MODEL_NUMBER] = number;
		return m;
	};

	static bool firstRun{true};
	if (firstRun) {
		firstRun = false;

		{
			auto& m = newMotor(46'096, "M54-40-S250-R", {"M54-40-S250-R"});
			m.converterFunctions = meta::buildConverters(251'417, 0, 0.00397746);
			m.defaultLayout[Register::TORQUE_LIMIT] = 120;
		}
		{
			auto& m = newMotor(43'288, "M42-10-S260-R", {"M42-10-S260-R"}); 
			m.converterFunctions = meta::buildConverters(263'187, 0, 0.00389076);
			m.defaultLayout[Register::TORQUE_LIMIT] = 300;
			m.defaultLayout[Register::MAX_POSITION_LIMIT] =  131'593;
			m.defaultLayout[Register::MIN_POSITION_LIMIT] = -131'593;
			m.defaultLayout[Register::VELOCITY_I_GAIN] =  72;
			m.defaultLayout[Register::VELOCITY_P_GAIN] = 520;
			m.defaultLayout[Register::POSITION_P_GAIN] =  32;
		}
		{
			auto& m = newMotor(54'024, "H54-200-S500-R", {"H54-200-S500-R"});
			m.converterFunctions = meta::buildConverters(501'923, 0, 0.00199234);
			m.defaultLayout[Register::TORQUE_LIMIT] = 620;
			m.defaultLayout[Register::VELOCITY_LIMIT] = 17'000;
			m.defaultLayout[Register::MAX_POSITION_LIMIT] =  250'961;
			m.defaultLayout[Register::MIN_POSITION_LIMIT] = -250'961;
			m.defaultLayout[Register::VELOCITY_I_GAIN] =  14;
			m.defaultLayout[Register::VELOCITY_P_GAIN] = 399;
			m.defaultLayout[Register::POSITION_P_GAIN] =  32;
		}

		{
			auto& m = newMotor(53'768, "H54-100-S500-R", {"H54-100-S500-R"});
			m.converterFunctions = meta::buildConverters(501'923, 0, 0.00199234);
			m.defaultLayout[Register::TORQUE_LIMIT] = 310;
			m.defaultLayout[Register::VELOCITY_LIMIT] = 17'000;
			m.defaultLayout[Register::MAX_POSITION_LIMIT] =  250'961;
			m.defaultLayout[Register::MIN_POSITION_LIMIT] = -250'961;
			m.defaultLayout[Register::VELOCITY_I_GAIN] =  16;
			m.defaultLayout[Register::VELOCITY_P_GAIN] = 256;
			m.defaultLayout[Register::POSITION_P_GAIN] =  32;
		}
		{
			auto& m = newMotor(51'200, "H42-20-S300-R", { "H42-20-S300-R"});
			m.converterFunctions = meta::buildConverters(303'750, 0, 0.00329218);
			m.defaultLayout[Register::ACCELERATION_LIMIT] =255;
			m.defaultLayout[Register::TORQUE_LIMIT] = 465;
			m.defaultLayout[Register::VELOCITY_LIMIT] = 10'300;
			m.defaultLayout[Register::MAX_POSITION_LIMIT] =  151'875;
			m.defaultLayout[Register::MIN_POSITION_LIMIT] = -151'875;
			m.defaultLayout[Register::VELOCITY_I_GAIN] =  40;
			m.defaultLayout[Register::VELOCITY_P_GAIN] = 440;
			m.defaultLayout[Register::POSITION_P_GAIN] =  32;
		}
	}
	return data;
};

}
