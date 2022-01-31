// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: MsgAttempts.proto

#include "MsgAttempts.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace reactor {
constexpr MsgAttempts::MsgAttempts(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : numofattempts_(0){}
struct MsgAttemptsDefaultTypeInternal {
  constexpr MsgAttemptsDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~MsgAttemptsDefaultTypeInternal() {}
  union {
    MsgAttempts _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT MsgAttemptsDefaultTypeInternal _MsgAttempts_default_instance_;
}  // namespace reactor
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_MsgAttempts_2eproto[1];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_MsgAttempts_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_MsgAttempts_2eproto = nullptr;

const uint32_t TableStruct_MsgAttempts_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::reactor::MsgAttempts, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::reactor::MsgAttempts, numofattempts_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::reactor::MsgAttempts)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::reactor::_MsgAttempts_default_instance_),
};

const char descriptor_table_protodef_MsgAttempts_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\021MsgAttempts.proto\022\007reactor\"$\n\013MsgAttem"
  "pts\022\025\n\rnumOfAttempts\030\002 \001(\005b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_MsgAttempts_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_MsgAttempts_2eproto = {
  false, false, 74, descriptor_table_protodef_MsgAttempts_2eproto, "MsgAttempts.proto", 
  &descriptor_table_MsgAttempts_2eproto_once, nullptr, 0, 1,
  schemas, file_default_instances, TableStruct_MsgAttempts_2eproto::offsets,
  file_level_metadata_MsgAttempts_2eproto, file_level_enum_descriptors_MsgAttempts_2eproto, file_level_service_descriptors_MsgAttempts_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_MsgAttempts_2eproto_getter() {
  return &descriptor_table_MsgAttempts_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_MsgAttempts_2eproto(&descriptor_table_MsgAttempts_2eproto);
namespace reactor {

// ===================================================================

class MsgAttempts::_Internal {
 public:
};

MsgAttempts::MsgAttempts(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor();
  if (!is_message_owned) {
    RegisterArenaDtor(arena);
  }
  // @@protoc_insertion_point(arena_constructor:reactor.MsgAttempts)
}
MsgAttempts::MsgAttempts(const MsgAttempts& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  numofattempts_ = from.numofattempts_;
  // @@protoc_insertion_point(copy_constructor:reactor.MsgAttempts)
}

inline void MsgAttempts::SharedCtor() {
numofattempts_ = 0;
}

MsgAttempts::~MsgAttempts() {
  // @@protoc_insertion_point(destructor:reactor.MsgAttempts)
  if (GetArenaForAllocation() != nullptr) return;
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

inline void MsgAttempts::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void MsgAttempts::ArenaDtor(void* object) {
  MsgAttempts* _this = reinterpret_cast< MsgAttempts* >(object);
  (void)_this;
}
void MsgAttempts::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void MsgAttempts::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void MsgAttempts::Clear() {
// @@protoc_insertion_point(message_clear_start:reactor.MsgAttempts)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  numofattempts_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MsgAttempts::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 numOfAttempts = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          numofattempts_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* MsgAttempts::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:reactor.MsgAttempts)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 numOfAttempts = 2;
  if (this->_internal_numofattempts() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_numofattempts(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:reactor.MsgAttempts)
  return target;
}

size_t MsgAttempts::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:reactor.MsgAttempts)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 numOfAttempts = 2;
  if (this->_internal_numofattempts() != 0) {
    total_size += ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32SizePlusOne(this->_internal_numofattempts());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData MsgAttempts::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSizeCheck,
    MsgAttempts::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*MsgAttempts::GetClassData() const { return &_class_data_; }

void MsgAttempts::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to,
                      const ::PROTOBUF_NAMESPACE_ID::Message& from) {
  static_cast<MsgAttempts *>(to)->MergeFrom(
      static_cast<const MsgAttempts &>(from));
}


void MsgAttempts::MergeFrom(const MsgAttempts& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:reactor.MsgAttempts)
  GOOGLE_DCHECK_NE(&from, this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_numofattempts() != 0) {
    _internal_set_numofattempts(from._internal_numofattempts());
  }
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void MsgAttempts::CopyFrom(const MsgAttempts& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:reactor.MsgAttempts)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MsgAttempts::IsInitialized() const {
  return true;
}

void MsgAttempts::InternalSwap(MsgAttempts* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(numofattempts_, other->numofattempts_);
}

::PROTOBUF_NAMESPACE_ID::Metadata MsgAttempts::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_MsgAttempts_2eproto_getter, &descriptor_table_MsgAttempts_2eproto_once,
      file_level_metadata_MsgAttempts_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace reactor
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::reactor::MsgAttempts* Arena::CreateMaybeMessage< ::reactor::MsgAttempts >(Arena* arena) {
  return Arena::CreateMessageInternal< ::reactor::MsgAttempts >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
