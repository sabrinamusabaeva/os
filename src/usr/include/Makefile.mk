SRC_USR_INCLUDE=$(SRC_DIR)/usr/include
BUILD_USR_INCLUDE=$(BUILD_DIR)/usr/include
BUILD_USR_INCLUDE_ALL = $(patsubst $(SRC_USR_INCLUDE)/%.h,$(BUILD_USR_INCLUDE)/%.h,$(shell find $(SRC_USR_INCLUDE) -name '*.h'))

$(BUILD_USR_INCLUDE)/%.h: $(SRC_USR_INCLUDE)/%.h
	mkdir -p $(dir $@)
	cp $< $@

