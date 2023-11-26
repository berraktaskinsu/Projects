# DI_Service_Lifetime

Dependency Injection - Service Lifetimes

* Transient: Create new implementation (object-service) when needed, do not re-use. EVERY TIME REQUESTED
* Scoped: (✳︎) New implementation for each scope (for each HTTP request). ONCE PER REQUEST
* Singleton: Single implementation for all usages, thoughout application lifetime. ONCE PER APPLICATION LIFETIME
