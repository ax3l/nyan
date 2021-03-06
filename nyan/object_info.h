// Copyright 2017-2017 the nyan authors, LGPLv3+. See copying.md for legal info.
#pragma once

#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "config.h"
#include "inheritance_change.h"
#include "location.h"
#include "member_info.h"
#include "ops.h"


namespace nyan {

class PatchInfo;
class State;


/**
 * Information about an object.
 * Used for the type system and error messages.
 */
class ObjectInfo {
public:
	using member_info_t = std::unordered_map<memberid_t, MemberInfo>;

	explicit ObjectInfo(const Location &location);
	~ObjectInfo() = default;

	const Location &get_location() const;

	MemberInfo &add_member(const memberid_t &name,
	                       MemberInfo &&member);

	member_info_t &get_members();
	const member_info_t &get_members() const;

	const MemberInfo *get_member(const memberid_t &name) const;

	PatchInfo &add_patch(const std::shared_ptr<PatchInfo> &info, bool initial);
	const std::shared_ptr<PatchInfo> &get_patch() const;

	void add_inheritance_change(InheritanceChange &&change);
	const std::vector<InheritanceChange> &get_inheritance_change() const;

	void set_linearization(std::vector<fqon_t> &&lin);
	const std::vector<fqon_t> &get_linearization() const;

	void set_children(std::unordered_set<fqon_t> &&children);
	const std::unordered_set<fqon_t> &get_children() const;

	bool is_patch() const;
	bool is_initial_patch() const;

	std::string str() const;

protected:
	/**
	 * Location where the object was defined.
	 */
	Location location;

	/**
	 * Is this object an initial patch?
	 * It is one when it was declared with <blabla>.
	 * Otherwise we just link to the parent that does.
	 */
	bool initial_patch;

	/**
	 * Patch target and modification information.
	 */
	std::shared_ptr<PatchInfo> patch_info;

	/**
	 * List of objects to add to the patch target.
	 */
	std::vector<InheritanceChange> inheritance_change;

	/**
	 * Maps members to their information.
	 */
	member_info_t member_info;

	/**
	 * Linearizations for the object when it was initially loaded.
	 */
	std::vector<fqon_t> initial_linearization;

	/**
	 * Direct children of the object at load time.
	 */
	std::unordered_set<fqon_t> initial_children;
};


} // namespace nyan
