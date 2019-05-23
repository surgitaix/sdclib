
	template <class WrapperType>
	static std::unique_ptr<typename WrapperType::WrappedType> convert(const WrapperType & source);

}; // class

} /* namespace SDC */
} /* namespace Data */
} /* namespace SDCLib */

#endif /* DATA_SDC_MDIB_CONVERTTOCDM_H_ */
